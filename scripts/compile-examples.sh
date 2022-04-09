#!/usr/bin/env bash

set -e

mkdir -p build

# for each directory in the examples folder, run processing-java on it
for dir in examples/*; do
  if [ -d "$dir" ]; then
    sketch=$dir/$(basename "$dir").ino
    if [ -f "$sketch" ]; then
      echo "Compiling $dir"
      arduino-cli compile --clean --fqbn arduino:avr:uno "$dir"
    else
      echo "Skipping $dir"
    fi
  fi
done
