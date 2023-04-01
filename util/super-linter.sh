#!/bin/bash

# PATH_TO_CODEBASE: The path to the codebase you want to lint. Don't use relative paths.
# PATH_TO_LINT_RULES: The path to the lint rules you want to use. Don't use relative paths.
# OPTIONS:
#  -i enters the super-linter container

# Example: ./super-linter.sh /path/to/codebase/to/be/check /path/to/.github/workflows from the root of the repo

PATH_TO_CODEBASE=$(realpath "$1")
PATH_TO_LINT_RULES=$(realpath "$2")
OPTIONS=""

# Exit if codebase is not provided.
if [ -z "$PATH_TO_CODEBASE" ]; then
  echo "Please provide the path to the codebase you want to lint."
  exit 1
fi

# Exit if lint rules are not provided.
if [ -z "$PATH_TO_LINT_RULES" ]; then
  echo "Please provide the path to the lint rules you want to use."
  exit 1
fi

if [ "$3" == "-i" ]; then
  OPTIONS="-it --entrypoint bash"
elif [ -n "$3" ]; then
  echo "Unrecognized option $3"
  exit 1
fi

# Exit if docker is not installed.
if ! [ -x "$(command -v docker)" ]; then
  echo 'Error: docker is not installed.' >&2
  exit 1
fi

# shellcheck disable=SC2086
docker run --rm \
    -e RUN_LOCAL=true \
    -e VALIDATE_GITHUB_ACTIONS=false \
    -e VALIDATE_CLANG_FORMAT=false \
    -e USE_FIND_ALGORITHM=true \
    -e VALIDATE_ALL_CODEBASE=false \
    -e MARKDOWN_CONFIG_FILE=../../../tmp/github/config/config.json \
    -e MARKDOWN_CUSTOM_RULE_GLOBS=../../../../tmp/github/rules/rules.js \
    -e LOG_LEVEL=WARN \
    -v "$PATH_TO_LINT_RULES":/tmp/github \
    -v "$PATH_TO_CODEBASE":/tmp/lint \
    $OPTIONS \
    github/super-linter:v4
