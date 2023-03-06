#!/bin/bash

curl -fsS https://dlang.org/install.sh | bash -s dmd
# shellcheck source=/dev/null
source "$(find ~/dlang -maxdepth 1 -name 'dmd-*')/activate"
