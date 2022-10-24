# Developer Notes

## Recipes

### Compile and test locally

1. [Install act](https://github.com/nektos/act#installation)
2. `act push -s GITHUB_TOKEN=$GITHUB_TOKEN`

### Create a GitHub release

Create a GitHub release. This was an older method of distribution before the
library was added to the Arduino aggregator. Use the Publish recipe instead (or
as well).

```shell
./scripts/release.sh # creates a GitHub release
```

### Publish

Package the distributable files into a zip file, and publish this file and the
library properties file to the location that the Arduino aggregator polls.

```shell
./scripts/publish.sh # uploads to static server
```

### Check the Arduino aggregator's build logs

Visit <http://downloads.arduino.cc/libraries/logs/github.com/osteele/Arduino_SerialRecord/>.

Note: The linter reports a warning that "Sketch(es) found outside examples and
extras folders". This is expected. It is because sketches that are used for
testing are in `./tests`. This directory is not included in the distribution zip
file. The linter examines the cloned repository, not the zip file.

There are possible workarounds for the warning. I considered the added
complexity that is necessary to implement any of these workarounds to be worse
than the warning.

## References

- [Arduino Library specification](https://arduino.github.io/arduino-cli/0.21/library-specification/#library-examples)
- <https://github.com/arduino/library-registry/blob/main/FAQ.md#how-can-i-add-a-library-to-library-manager>
