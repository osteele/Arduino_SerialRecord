#!/usr/bin/env bash

set -e

PATH="/opt/homebrew/opt/grep/libexec/gnubin:$PATH"

project_file=library.properties
name=$(grep -oP '^name=\K.+' $project_file)

zip_file=dist/${name}.zip

mkdir -p dist
rm -f "$zip_file"
zip -qr "$zip_file" docs examples keywords.txt library.properties LICENSE* README* *.h

echo "${zip_file}"
