#!/bin/bash

if test "$#" -ne 1; then
    echo "$0 software-stack | data | compute | io | app-interact" 1>&2
    exit 1
fi

# Only proceed if repository is clean.
# Long live StackExchange: https://unix.stackexchange.com/a/155077/227174
output=$(git status --untracked-files=no --porcelain)
if test ! -z "$output"; then
    echo "Repository is not clean. Run 'git status' to see uncommitted changes." 1>&2
    echo "Please commit / clean your changes before update." 1>&2
    exit 1
fi

git checkout master

case "$1" in

    "software-stack")
        # Clean branches and everything.
        git remote rm razvand > /dev/null 2>&1
        git branch -D software-stack-lab-readme > /dev/null 2>&1

        git remote add razvand https://github.com/razvand/operating-systems-oer
        git fetch razvand
        git checkout -b software-stack-lab-readme razvand/software-stack-lab-readme
        ;;

    "data")
        # Clean branches and everything.
        git remote rm RazvanN7 > /dev/null 2>&1
        git branch -D Data_lab > /dev/null 2>&1

        git remote add RazvanN7 https://github.com/RazvanN7/operating-systems-oer
        git fetch RazvanN7
        git checkout -b Data_lab RazvanN7/Data_lab
        ;;

    "compute")
        # Clean branches and everything.
        git remote rm teodutu > /dev/null 2>&1
        git branch -D compute-lab > /dev/null 2>&1

        git remote add teodutu https://github.com/teodutu/operating-systems-oer
        git fetch teodutu
        git checkout -b compute-lab teodutu/compute-lab
        ;;

    "io")
        # Clean branches and everything.
        git remote rm Alex-deVis > /dev/null 2>&1
        git branch -D io-lab > /dev/null 2>&1

        git remote add teodutu https://github.com/Alex-deVis/operating-systems-oer
        git fetch Alex-deVis
        git checkout -b io-lab Alex-deVis/io-lab
        ;;

    "app-interact")
        # Clean branches and everything.
        git remote rm molecula2788 > /dev/null 2>&1
        git branch -D app-interact-lab-work > /dev/null 2>&1

        git remote add molecula2788 https://github.com/molecula2788/operating-systems-oer
        git fetch molecula2788
        git checkout -b app-interact-lab-work molecula2788/app-interact-lab-work
        ;;

esac
