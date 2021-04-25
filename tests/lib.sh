printf '== %s\n' "$0"
trap "printf '\n'" EXIT

begin() {
    trmcols=$(stty size | cut -d' ' -f2)
    padding=$(($trmcols - 5))
    printf "%-${padding}s" "$1"
}

failure() {
    printf 'FAIL\n'
}

success() {
    printf '  OK\n'
}

expect() {
    expect_=$1
    shift
    got="$(tests/pilot $@)"

    if [ "$got" != "$expect_" ]
    then
        failure
        printf '\texpected "%s"\t\tgot "%s"\n' "$expect_" "$got"
    else
        success
    fi
}

chkend() {
    if [ $? -eq 0 ]; then success; else failure; fi
}
