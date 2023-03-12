#!/bin/bash

# Configure terminal
# shellcheck disable=2154
PS1='🐳 ${debian_chroot:+($debian_chroot)}\[\033[01;36m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
PROMPT_DIRTRIM=3

# Add aliases for labs
# shellcheck disable=1007
ALIAS_DESC= cat << EOF
Shortcuts:
go-ss       - changes directory to Software-Stack lab
go-data     - changes directory to Data lab
go-compute  - changes directory to Compute lab
go-io       - changes directory to IO lab
go-appInt   - changes directory to App Interaction lab
EOF
echo "$ALIAS_DESC"

CHAPTERS_PATH="$HOME/operating-systems/content/chapters"
alias go-ss="cd \$CHAPTERS_PATH/software-stack/lab/"
alias go-data="cd \$CHAPTERS_PATH/data/lab/"
alias go-compute="cd \$CHAPTERS_PATH/compute/lab/"
alias go-io="cd \$CHAPTERS_PATH/io/lab/"
alias go-appInt="cd '\$CHAPTERS_PATH/app-interact/lab/"
