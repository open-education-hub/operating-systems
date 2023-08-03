#!/bin/bash

find /usr/bin /bin /usr/sbin /sbin -type f -exec file {} \; |
    awk '
BEGIN {
    num_bin = 0;
    num_perl = 0;
    num_shell = 0;
    num_python = 0;
    num_others = 0;
}

/.*shell script.*/ {
    num_shell++;
    next;
}

/.*Perl script.*/ {
    num_perl++;
    next;
}

/.*ython(|3) script.*/ {
    num_python++;
    next;
}

/.*ELF.*LSB.*/ {
    num_bin++;
    next;
}

{
    num_others++;
}

END {
    print "binary apps:", num_bin;
    print "Perl apps:", num_perl;
    print "Shell apps:", num_shell;
    print "Python apps:", num_python;
    print "Other apps:", num_others;
}'
