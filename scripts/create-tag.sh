#!/usr/bin/env bash

set -e

PATH="/opt/homebrew/opt/grep/libexec/gnubin:$PATH"

project_file=library.properties
version=$(grep -oP '^version=\K.+' $project_file)

mkdir -p dist

# if dist/release does not exist, create a git worktree
if [ ! -d dist/release ]; then
  git worktree remove --force dist/release 2> /dev/null || true
  git worktree add --no-checkout dist/release release
fi

# remove the worktree on exit
# trap 'git worktree remove --force dist/release' EXIT

# # remove the previous contents of dist/release
rm -rf dist/release/*

# # create the zip and uncompress it into dist/release
zip_file=$(./scripts/create-zip.sh)
unzip -q "$zip_file" -d dist/release

cd dist/release
# remove files that aren't in the workspace from the git index
git add -A
git commit -m "Version ${version}"
git tag -a "${version}" -m "Version ${version}"
