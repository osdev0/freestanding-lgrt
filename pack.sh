#! /bin/sh
#
# Part of cc-runtime, under the Apache License v2.0 with LLVM Exceptions.
# See LICENSE.TXT for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set -ex

# Preprocessor guard for the per-architecture subdirectories of src/, mirroring
# the per-architecture source lists of upstream compiler-rt.
arch_guard() {
    case "$1" in
        src/aarch64/*) echo 'defined(__aarch64__)' ;;
        src/arm/*) echo 'defined(__arm__)' ;;
        src/riscv/*) echo 'defined(__riscv)' ;;
    esac
}

# Preprocessor guard for an assembly source.
asm_guard() {
    guard=$(arch_guard "$1")
    case "$1" in
        # 32-bit ARM assembly is built in ARM state, as Thumb2, and as Thumb1
        # from ARMv6 on.
        src/arm/*) guard="$guard && (!defined(__thumb__) || defined(__thumb2__) || __ARM_ARCH >= 6)" ;;
        src/riscv/mulsi3.S) guard="$guard && __riscv_xlen == 32" ;;
        src/riscv/muldi3.S) guard="$guard && __riscv_xlen == 64" ;;
    esac
    echo "${guard:-1}"
}

# As in upstream's build, an assembly source supersedes the generic C source of
# the same name where it is used.
supersede_guard() {
    name=$(basename "$1" .c)
    guards=
    for s in src/*/"$name".S; do
        if [ -f "$s" ]; then
            guards="${guards:+$guards || }($(asm_guard "$s"))"
        fi
    done
    echo "$guards"
}

# Prints an assembly source with its quoted includes inlined. The includes of
# the headers that are part of the packed prelude are replaced by a marker.
cat >asm-inline.awk <<'EOF'
function emit(path,    dir, line, inc, base) {
    dir = path
    sub(/[^\/]*$/, "", dir)
    while ((getline line < path) > 0) {
        if (line ~ /^[ \t]*#[ \t]*include[ \t]*"/) {
            inc = line
            sub(/^[^"]*"/, "", inc)
            sub(/".*$/, "", inc)
            base = inc
            sub(/^.*\//, "", base)
            if (base == "assembly.h" || base == "int_endianness.h")
                print "@prelude@"
            else
                emit(dir inc)
            continue
        }
        print line
    }
    close(path)
}

BEGIN {
    emit(ARGV[1])
    exit
}
EOF

# Converts an assembly source, as printed by asm-inline.awk, to C. Preprocessor
# directives are kept as they are, and the assembly lines become top-level
# __asm__ statements. The invocations of the macros that the assembly source
# itself can see are expanded by the C preprocessor through CC_RUNTIME_ASM,
# everything else is emitted verbatim in string literals. As the converted
# code is assembly, __ASSEMBLER__ is considered defined in the directives.
#
# With hygiene set, the code gets its own .pushsection, and the macros and
# assembler macros it defines are undefined afterwards, as if it were a
# translation unit of its own.
cat >asm-to-c.awk <<'EOF'
function fail(msg) {
    printf "pack.sh: %s\n", msg | "cat 1>&2"
    close("cat 1>&2")
    exit 1
}

# Index of the quote closing the literal opened at i, or 0 if it is unclosed.
function literal_end(s, i,    q, j, c) {
    q = substr(s, i, 1)
    for (j = i + 1; j <= length(s); j++) {
        c = substr(s, j, 1)
        if (c == "\\")
            j++
        else if (c == q)
            return j
    }
    return 0
}

# Index of the parenthesis closing the one at i, or 0 if it is unclosed.
function paren_end(s, i,    depth, j, c) {
    depth = 0
    for (j = i; j <= length(s); j++) {
        c = substr(s, j, 1)
        if (c == "\"" && literal_end(s, j))
            j = literal_end(s, j)
        else if (c == "(")
            depth++
        else if (c == ")" && --depth == 0)
            return j
    }
    return 0
}

# Removes the comments from a line, keeping track of block comments.
function strip(l,    out, i, c, j) {
    out = ""
    i = 1
    while (i <= length(l)) {
        c = substr(l, i, 1)
        if (incomment) {
            if (substr(l, i, 2) == "*/") {
                incomment = 0
                out = out " "
                i += 2
            } else
                i++
        } else if (substr(l, i, 2) == "/*") {
            incomment = 1
            i += 2
        } else if (substr(l, i, 2) == "//") {
            break
        } else if ((c == "\"" || c == "'") && (j = literal_end(l, i))) {
            out = out substr(l, i, j - i + 1)
            i = j + 1
        } else {
            out = out c
            i++
        }
    }
    return out
}

function esc(r,    out, i, c) {
    out = ""
    for (i = 1; i <= length(r); i++) {
        c = substr(r, i, 1)
        if (c == "\\" || c == "\"")
            out = out "\\" c
        else if (c == "?")
            out = out "\\?"
        else if (c == "\t")
            out = out "\\t"
        else if (c == "\n")
            out = out "\\n"
        else
            out = out c
    }
    return out
}

function lit(r) {
    return r == "" ? "" : " \"" esc(r) "\""
}

function convert(s,    out, raw, i, c, j, k, word, inv) {
    out = ""
    raw = ""
    i = 1
    while (i <= length(s)) {
        c = substr(s, i, 1)
        if (c == "\"" && (j = literal_end(s, i))) {
            raw = raw substr(s, i, j - i + 1)
            i = j + 1
        } else if (c ~ /[0-9]/ || (c == "." && substr(s, i + 1, 1) ~ /[0-9]/)) {
            for (j = i + 1; j <= length(s); j++) {
                k = substr(s, j, 1)
                if (k ~ /[0-9A-Za-z_.]/)
                    continue
                if ((k == "+" || k == "-") && substr(s, j - 1, 1) ~ /[eEpP]/)
                    continue
                break
            }
            raw = raw substr(s, i, j - i)
            i = j
        } else if (c ~ /[A-Za-z_$]/) {
            for (j = i + 1; j <= length(s) && substr(s, j, 1) ~ /[A-Za-z0-9_$]/; j++)
                ;
            word = substr(s, i, j - i)
            if (word in known) {
                for (k = j; k <= length(s) && substr(s, k, 1) ~ /[ \t]/; k++)
                    ;
                if (substr(s, k, 1) == "(") {
                    if (!(k = paren_end(s, k)))
                        fail("unbalanced macro invocation: " s)
                    j = k + 1
                }
                inv = substr(s, i, j - i)
                if (inv ~ /[\\']/)
                    fail("macro invocation cannot be stringified: " inv)
                out = out lit(raw) " CC_RUNTIME_ASM(" inv ")"
                raw = ""
            } else {
                raw = raw word
            }
            i = j
        } else {
            raw = raw c
            i++
        }
    }
    return substr(out lit(raw "\n"), 2)
}

function close_run() {
    if (run) {
        print ");"
        run = 0
    }
}

function emit(s,    name) {
    if (s ~ /^[ \t]*$/ || s == "@prelude@")
        return
    if (s ~ /^[ \t]*#/) {
        close_run()
        if (s ~ /^[ \t]*#[ \t]*include[ \t]/)
            return
        if (s ~ /^[ \t]*#[ \t]*ifdef[ \t]+__ASSEMBLER__[ \t]*$/)
            s = "#if 1"
        else if (s ~ /^[ \t]*#[ \t]*ifndef[ \t]+__ASSEMBLER__[ \t]*$/)
            s = "#if 0"
        gsub(/defined[ \t]*\([ \t]*__ASSEMBLER__[ \t]*\)/, "1", s)
        gsub(/defined[ \t]+__ASSEMBLER__/, "1", s)
        print s
        return
    }
    if (s ~ /^[ \t]*\.macro[ \t]/) {
        name = s
        sub(/^[ \t]*\.macro[ \t]+/, "", name)
        sub(/[ \t,].*$/, "", name)
        asm_macros[++nasm_macros] = name
    }
    # Runs are kept short, so that the string literals they concatenate to stay
    # within the length that C requires compilers to support.
    if (run == 16)
        close_run()
    if (!run)
        print "__asm__("
    run++
    print "    " convert(s)
}

BEGIN {
    n = split(prelude_macros, t, " ")
    for (i = 1; i <= n; i++)
        prelude[t[i]] = 1
}

{
    src[++nsrc] = $0
}

END {
    # Splice continued lines and remove comments, like the preprocessor does.
    for (i = 1; i <= nsrc; i++) {
        l = src[i]
        while (l ~ /\\$/ && i < nsrc)
            l = substr(l, 1, length(l) - 1) src[++i]
        pending = have ? pending " " strip(l) : strip(l)
        have = 1
        if (!incomment) {
            lines[++nlines] = pending
            have = 0
        }
    }

    for (i = 1; i <= nlines; i++) {
        if (lines[i] == "@prelude@") {
            for (name in prelude)
                known[name] = 1
        } else if (lines[i] ~ /^[ \t]*#[ \t]*define[ \t]/) {
            name = lines[i]
            sub(/^[ \t]*#[ \t]*define[ \t]+/, "", name)
            match(name, /^[A-Za-z_][A-Za-z0-9_]*/)
            name = substr(name, 1, RLENGTH)
            known[name] = 1
            if (!(name in prelude) && !(name in defined))
                macros[++nmacros] = name
            defined[name] = 1
        }
    }

    if (hygiene)
        print "__asm__(\".pushsection .text\\n\");"
    for (i = 1; i <= nlines; i++)
        emit(lines[i])
    close_run()
    if (hygiene) {
        print "__asm__(\".popsection\\n\");"
        for (i = 1; i <= nasm_macros; i++)
            print "__asm__(\".purgem " asm_macros[i] "\\n\");"
        for (i = 1; i <= nmacros; i++)
            print "#undef " macros[i]
    }
}
EOF

# Specializes converted code for one instantiation: the conditionals that only
# depend on the instantiation parameters (the controlled macros, which have
# the given values) are evaluated, the others are kept. Adjacent __asm__
# statements are then merged, and undefining macros that are never defined
# is skipped.
cat >asm-instance.awk <<'EOF'
function tokenize(s,    i, j, c, two) {
    ntok = 0
    for (i = 1; i <= length(s); ) {
        c = substr(s, i, 1)
        two = substr(s, i, 2)
        if (c ~ /[ \t]/) {
            i++
        } else if (c ~ /[A-Za-z_0-9]/) {
            for (j = i + 1; j <= length(s) && substr(s, j, 1) ~ /[A-Za-z_0-9]/; j++)
                ;
            tok[++ntok] = substr(s, i, j - i)
            i = j
        } else if (two == "&&" || two == "||" || two == "==" || two == "!=" ||
                   two == "<=" || two == ">=") {
            tok[++ntok] = two
            i += 2
        } else if (c ~ /[()!<>]/) {
            tok[++ntok] = c
            i++
        } else {
            return 0
        }
    }
    tok[ntok + 1] = ""
    return 1
}

function primary(    t, name, v) {
    t = tok[pos++]
    if (t == "(") {
        v = or_expr()
        if (tok[pos++] != ")")
            unknown = 1
        return v
    }
    if (t == "defined") {
        if (tok[pos] == "(") {
            name = tok[pos + 1]
            if (tok[pos + 2] != ")")
                unknown = 1
            pos += 3
        } else {
            name = tok[pos++]
        }
        if (!(name in controlled))
            unknown = 1
        return name in value
    }
    if (t ~ /^[0-9]+$/)
        return t + 0
    if (!(t in controlled))
        unknown = 1
    return value[t] + 0
}

function unary_expr() {
    if (tok[pos] == "!") {
        pos++
        return !unary_expr()
    }
    return primary()
}

function rel_expr(    v, op, r) {
    v = unary_expr()
    while (tok[pos] ~ /^[<>]=?$/) {
        op = tok[pos++]
        r = unary_expr()
        v = op == "<" ? v < r : op == ">" ? v > r : op == "<=" ? v <= r : v >= r
    }
    return v
}

function eq_expr(    v, op, r) {
    v = rel_expr()
    while (tok[pos] == "==" || tok[pos] == "!=") {
        op = tok[pos++]
        r = rel_expr()
        v = op == "==" ? v == r : v != r
    }
    return v
}

function and_expr(    v, r) {
    v = eq_expr()
    while (tok[pos] == "&&") {
        pos++
        r = eq_expr()
        v = v && r
    }
    return v
}

function or_expr(    v, r) {
    v = and_expr()
    while (tok[pos] == "||") {
        pos++
        r = and_expr()
        v = v || r
    }
    return v
}

# 1 or 0 if the expression only depends on controlled macros, -1 otherwise.
function evaluate(s,    v) {
    unknown = 0
    if (!tokenize(s))
        return -1
    pos = 1
    v = or_expr()
    return unknown || pos != ntok + 1 ? -1 : v ? 1 : 0
}

function out(l,    name) {
    if (l ~ /^[ \t]*#[ \t]*(define|undef)[ \t]/) {
        name = l
        sub(/^[ \t]*#[ \t]*(define|undef)[ \t]+/, "", name)
        match(name, /^[A-Za-z_][A-Za-z0-9_]*/)
        name = substr(name, 1, RLENGTH)
        if (l ~ /^[ \t]*#[ \t]*define/)
            seen[name] = 1
        else if (!(name in seen))
            return
    }
    if (held) {
        held = 0
        if (l == "__asm__(")
            return
        print ");"
    }
    if (l == ");")
        held = 1
    else
        print l
}

BEGIN {
    n = split(controlled_macros, t, " ")
    for (i = 1; i <= n; i++)
        controlled[t[i]] = 1
    n = split(values, t, " ")
    for (i = 1; i <= n; i++) {
        split(t[i], kv, "=")
        value[kv[1]] = kv[2]
    }
    depth = 0
    active[0] = 1
}

{
    l = $0
    d = ""
    if (match(l, /^[ \t]*#[ \t]*[a-z]+/)) {
        d = substr(l, RSTART, RLENGTH)
        sub(/^[ \t]*#[ \t]*/, "", d)
        rest = substr(l, RSTART + RLENGTH)
    }
    if (d == "if" || d == "ifdef" || d == "ifndef") {
        depth++
        dead[depth] = !active[depth - 1]
        if (dead[depth]) {
            active[depth] = 0
            next
        }
        if (d == "ifdef")
            rest = "defined(" rest ")"
        else if (d == "ifndef")
            rest = "!defined(" rest ")"
        v = evaluate(rest)
        kept[depth] = v == -1
        taken[depth] = v == 1
        active[depth] = v != 0
        if (kept[depth])
            out(l)
    } else if (d == "elif") {
        if (dead[depth])
            next
        if (taken[depth]) {
            active[depth] = 0
            next
        }
        v = evaluate(rest)
        if (v == 1) {
            if (kept[depth])
                out("#else")
            taken[depth] = 1
        } else if (v == -1) {
            out(kept[depth] ? l : "#if" rest)
            kept[depth] = 1
        }
        active[depth] = v != 0
    } else if (d == "else") {
        if (dead[depth])
            next
        active[depth] = !taken[depth]
        if (kept[depth] && !taken[depth])
            out(l)
        taken[depth] = 1
    } else if (d == "endif") {
        if (!dead[depth] && kept[depth])
            out(l)
        depth--
    } else if (active[depth]) {
        out(l)
    }
}

END {
    if (held)
        print ");"
}
EOF

asm_to_c() {
    awk -f asm-inline.awk "$1" | awk -v prelude_macros="$prelude_macros" -v hygiene="$2" -f asm-to-c.awk
}

prelude_macros=$(sed -n 's/^[[:space:]]*#[[:space:]]*define[[:space:]]\{1,\}\([A-Za-z_][A-Za-z0-9_]*\).*/\1/p' \
    src/int_endianness.h src/assembly.h | tr '\n' ' ')

cat >src/cc-runtime.c <<'EOF'
#pragma GCC diagnostic ignored "-Wunused-function"

#define CC_RUNTIME_ASM_STR(...) #__VA_ARGS__
#define CC_RUNTIME_ASM(...) CC_RUNTIME_ASM_STR(__VA_ARGS__)

EOF

cat src/int_endianness.h >> src/cc-runtime.c
asm_to_c src/assembly.h 0 >> src/cc-runtime.c
cat src/int_types.h src/int_lib.h src/int_util.h >> src/cc-runtime.c

for f in $(find src -name '*.c' | grep -v 'cc-runtime\.c' | LC_ALL=C sort); do
    guard=$(arch_guard "$f")
    superseded=$(supersede_guard "$f")
    if [ -n "$superseded" ]; then
        guard="${guard:+$guard && }!($superseded)"
    fi
    if [ -n "$guard" ]; then
        echo "#if $guard"
    fi
    cat "$f"
    if [ -n "$guard" ]; then
        echo "#endif"
    fi
done >> src/cc-runtime.c

for f in $(cd src && echo *.inc); do
    sed -e "/#include \"$f\"/{r src/$f" -e "d}" src/cc-runtime.c > src/cc-runtime.c.tmp
    mv src/cc-runtime.c.tmp src/cc-runtime.c
done

for f in $(find src -name '*.S' | LC_ALL=C sort); do
    echo "#if $(asm_guard "$f")"
    case "$f" in
        src/aarch64/lse.S)
            # Instantiated for each pattern, size and model, as in upstream's
            # build.
            asm_to_c "$f" 1 > asm-lse.tmp
            for pat in cas swp ldadd ldclr ldeor ldset; do
                for size in 1 2 4 8 16; do
                    if [ "$size" = 16 ] && [ "$pat" != cas ]; then
                        continue
                    fi
                    for model in 1 2 3 4 5; do
                        printf '#define L_%s\n#define SIZE %s\n#define MODEL %s\n' "$pat" "$size" "$model"
                        awk \
                            -v controlled_macros="L_cas L_swp L_ldadd L_ldclr L_ldeor L_ldset SIZE MODEL" \
                            -v values="L_$pat= SIZE=$size MODEL=$model" -f asm-instance.awk asm-lse.tmp
                        printf '#undef L_%s\n#undef SIZE\n#undef MODEL\n' "$pat"
                    done
                done
            done
            ;;
        *)
            asm_to_c "$f" 1
            ;;
    esac
    echo "#endif"
done >> src/cc-runtime.c

cat >>src/cc-runtime.c <<'EOF'

#undef CC_RUNTIME_ASM_STR
#undef CC_RUNTIME_ASM
EOF

rm -f asm-inline.awk asm-to-c.awk asm-instance.awk asm-lse.tmp

# System headers go to the top, except stdatomic.h, which the C11 functions
# include only where their guard lets them be built.
grep '#include <' src/cc-runtime.c | grep -v '<stdatomic\.h>' > saved-includes
sed -e '/#include <stdatomic\.h>/b' -e '/#include/d' src/cc-runtime.c > src/cc-runtime.c.tmp
mv src/cc-runtime.c.tmp src/cc-runtime.c
cat saved-includes src/cc-runtime.c > src/cc-runtime.c.tmp
mv src/cc-runtime.c.tmp src/cc-runtime.c
rm -f saved-includes

awk '{for(x=1;x<=NF;x++)if($x~/_EXTERNAL_COUNTER/){sub(/_EXTERNAL_COUNTER/,++i)}}1' src/cc-runtime.c > src/cc-runtime.c.tmp
mv src/cc-runtime.c.tmp src/cc-runtime.c

# The packed file starts with the license and credits, then a gate that stops
# the build where cc-runtime isn't supported, before any header can fail.
sed -e 's|^|// |' -e 's| *$||' LICENSE.TXT > packed-header
echo '//' >> packed-header
echo '// ---- Start of embedded CREDITS.TXT, as referred to above ----' >> packed-header
echo '//' >> packed-header
sed -e 's|^|// |' -e 's| *$||' CREDITS.TXT >> packed-header
echo '//' >> packed-header
echo '// ---- End of embedded CREDITS.TXT ----' >> packed-header
echo >> packed-header
cat >>packed-header <<'EOF'
// Only GCC and Clang, building ELF objects for x86 (including 16-bit code),
// AArch64, ARM, RISC-V or LoongArch, are supported.
#if !defined(__clang__) &&                                                     \
    (!defined(__GNUC__) || defined(__INTEL_COMPILER) ||                        \
     defined(__NVCOMPILER) || defined(__PGI) || defined(_CRAYC) ||             \
     defined(__TINYC__) || defined(__PCC__) || defined(__LCC__) ||             \
     defined(__COMPCERT__) || defined(__CC_ARM) ||                             \
     defined(__TI_COMPILER_VERSION__))
#error "cc-runtime: unsupported compiler, use GCC or Clang"
#endif
// Workaround: Clang up to 16, bare-metal x86, AArch64 and LoongArch: it does
// not always define __ELF__, so only targets known not to be ELF are ruled out.
#if !defined(__ELF__) &&                                                       \
    (!defined(__clang__) || __clang_major__ >= 17 || defined(_WIN32) ||        \
     defined(__CYGWIN__) || defined(__APPLE__) || defined(__MACH__))
#error "cc-runtime: unsupported object format, only ELF is supported"
#endif
#if !defined(__x86_64__) && !defined(__i386__) && !defined(__ia16__) &&        \
    !defined(__aarch64__) && !defined(__arm__) && !defined(__riscv) &&         \
    !defined(__loongarch__)
#error "cc-runtime: unsupported architecture"
#endif

EOF
cat packed-header src/cc-runtime.c > src/cc-runtime.c.tmp
mv src/cc-runtime.c.tmp src/cc-runtime.c
rm -f packed-header
