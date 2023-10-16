#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

# Grade style based on build warnings and linter warnings / errors.
# Points are subtracted from the maximum amount of style points (10).
#   - For 15 or more build warnings, all points (10) are subtracted.
#   - For [10,15) build warnings, 6 points are subtracted.
#   - For [5,10) build warnings, 4 points are subtracted.
#   - For [1,5) build warnings, 2 points are subtracted.
#   - For 25 ore more linter warnings / errors, all points (10) are subtracted.
#   - For [15,25) linter warnings / errors, 6 points are subtracted.
#   - For [7,15) linter warnings / errors, 4 points are subtracted.
#   - For [1,7) linter warnings / errors, 2 points are subtracted.
# Final style points are between 0 and 10. Results cannot be negative.
#
# Result (grade) is stored in style_grade.out file.
# Collect summary in style_summary.out file.

function grade_style()
{
    compiler_warn=$(< checker.out grep -v 'unused parameter' | grep -v 'unused variable' | \
        grep -v "discards 'const'" | grep -c '[0-9]\+:[0-9]\+: warning:')

    compiler_down=0
    if test "$compiler_warn" -ge 15; then
        compiler_down=10
    elif test "$compiler_warn" -ge 10; then
        compiler_down=6
    elif test "$compiler_warn" -ge 5; then
        compiler_down=4
    elif test "$compiler_warn" -ge 1; then
        compiler_down=2
    fi

    cpplint=$(< linter.out grep "Total errors found:" | rev | cut -d ' ' -f 1 | rev)
    checkpatch_err=$(< linter.out grep 'total: [0-9]* errors' | grep -o '[0-9]* errors,' | \
        cut -d ' ' -f 1 | paste -s -d '+' | bc)
    checkpatch_warn=$(< linter.out grep 'total: [0-9]* errors' | grep -o '[0-9]* warnings,' | \
        cut -d ' ' -f 1 | paste -s -d '+' | bc)
    if test -z "$checkpatch_err"; then
        checkpatch_err=0
    fi
    if test -z "$checkpatch_warn"; then
        checkpatch_warn=0
    fi
    checkpatch=$((checkpatch_err + checkpatch_warn))
    checker_all=$((cpplint + checkpatch))

    checker_down=0
    if test "$checker_all" -ge 25; then
        checker_down=10
    elif test "$checker_all" -ge 15; then
        checker_down=6
    elif test "$checker_all" -ge 7; then
        checker_down=4
    elif test "$checker_all" -ge 1; then
        checker_down=2
    fi

    full_down=$((compiler_down + checker_down))

    if test "$full_down" -gt 10; then
        full_down=10
    fi
    style_grade=$((10 - full_down))

    echo "$style_grade" > style_grade.out

    {
        < linter.out grep -v 'unused parameter' | grep -v 'unused variable' | grep -v "discards 'const'" | \
            grep '[0-9]\+:[0-9]\+: warning:'
        < linter.out grep "Total errors found: [1-9]"
        < linter.out grep 'total: [1-9]* errors'
        < linter.out grep 'total: 0 errors' | grep '[1-9][0-9]* warnings'
    } > style_summary.out
}

# Print grades: total, checker and style.
# Style grade is only awarded for assignments that have past 60 points
# of th checker grade.
print_results()
{
    checker_grade=$(< checker.out sed -n '/^Checker:/s/^.*[ \t]\+\([0-9\.]\+\)\/.*$/\1/p')
    if test "$(echo "$checker_grade > 60" | bc)" -eq 1; then
        style_grade=$(cat style_grade.out)
    else
        style_grade=0
    fi
    final_grade=$(echo "scale=2; $checker_grade+$style_grade" | bc)
    echo -e "\n\n### GRADE\n\n"
    printf "Checker: %58s/ 90\n" "$checker_grade"
    printf "Style: %60s/ 10\n" "$style_grade"
    printf "Total: %60s/100\n" "$final_grade"

    echo -e "\n\n### STYLE SUMMARY\n\n"
    cat style_summary.out
}

run_interactive()
{
    echo -e "\n\n### CHECKER\n\n"
    stdbuf -oL make check 2>&1 | stdbuf -oL sed 's/^Total:/Checker:/g' | tee checker.out

    echo -e "\n\n### LINTER\n\n"
    stdbuf -oL make lint 2>&1 | tee linter.out

    grade_style
    print_results
}

run_non_interactive()
{
    make check 2>&1 | sed 's/^Total:/Checker:/g' > checker.out
    make lint > linter.out 2>&1

    grade_style
    print_results

    echo -e "\n\n### CHECKER\n\n"
    cat checker.out

    echo -e "\n\n### LINTER\n\n"
    cat linter.out
}

# In case of a command line argument disable interactive output.
# That is, do not show output as it generated.
# This is useful to collect all output and present final results at the
# beginning of the script output.
# This is because Moodle limits the output results, and the final results
# would otherwise not show up.
if test $# -eq 0; then
    run_interactive
else
    run_non_interactive
fi
