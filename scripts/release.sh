#!/usr/bin/env bash

set -e

# on macOS, requires `brew install grep`
PATH="/opt/homebrew/opt/grep/libexec/gnubin:$PATH"
OWNER=osteele
REPO=Arduino_SerialRecord

project_file=library.properties
name=$(grep -oP '^name=\K.+' $project_file)
version=$(grep -oP '^version=\K.+' $project_file)
tag="v${version}"

zip_file=dist/${name}.zip

# DRY release.sh
# mkdir -p dist
# rm -f "$zip_file"
# zip -qr "$zip_file" docs examples library.properties LICENSE* README* *.h

git tag -af "${tag}" -m "Release $version"
git push origin "${tag}"

curl \
  -X POST \
  -H "Accept: application/vnd.github.v3+json" \
  https://api.github.com/repos/octocat/hello-world/releases \
  -d "{\"owner\":\"${OWNER}\",\"repo\":\"${REPO}\",\"tag_name\":\"${tag}\","draft":true}"

open dist
open https://github.com/${OWNER}/${REPO}/releases/new
