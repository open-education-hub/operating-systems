#!/bin/bash

if [ "$(uname -m)" = "x86_64" ]; then
  curl -fsS https://dlang.org/install.sh | sed 's/--connect-timeout 5/--connect-timeout 15/g' | bash -s dmd
  # shellcheck source=/dev/null
  source "$(find ~/dlang -maxdepth 1 -name 'dmd-*')/activate"
fi


if [ "$(uname -m)" = "aarch64" ]; then
  curl -fsS https://dlang.org/install.sh | sed 's/--connect-timeout 5/--connect-timeout 15/g' | bash -s ldc
  # shellcheck source=/dev/null
  source "$(find ~/dlang -maxdepth 1 -name 'ldc-*')/activate"
fi
