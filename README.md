# Serial Record Library for Arduino

[![Arduino Lint](https://github.com/osteele/Arduino_SerialRecord/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/osteele/Arduino_SerialRecord/actions/workflows/arduino-lint.yml)
[![Compile Examples](https://github.com/osteele/Arduino_SerialRecord/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/osteele/Arduino_SerialRecord/actions/workflows/compile-examples.yml)

The [SerialRecord library for Arduino](https://osteele.github.io/Arduino_SerialRecord/) sends and receive *records, containing multiple* integers, over the serial port.

This library is intended for novice programmers. It is designed to be easy to use, to detect when it is used incorrectly, to detect and report when it receives invalid data. Data is sent and received as comma-separated ASCII with optional field names, for ease of inspection with the Serial Monitor and for compatibility with the Serial Plotter and with Processing sketches that also use this format.

The library can be used with the [SerialRecord library for Processing
4](https://osteele.github.io/Processing_SerialRecord/), but does not require it.

![](docs/screenshot.png "Screenshot")

[SerialRecord library for Processing 4]: https://osteele.github.io/Processing_SerialRecord/

## Design Goals

- Easy for novice programmers to configure and use
- Easy to inspect the transmitted data
- Detects and provides diagnostics for common errors

### Non-goals

- Efficiency. The library uses an ASCII representation of numbers. This is easy
  to visually inspect without tools, but it is computationally expensive to read
  and write, and requires more bandwidth than a binary representation.
- Flexibility. All records must have the same number of values; only integers
  are supported. This makes it possible to detect errors in code that uses the
  library, but is not appropriate to all communications. If you need more
  flexibility, this is not the library for you. (See the Alternatives section
  below.)

## Features

- Send an "!e" to the sketch to send received the values array back to the serial
  port. (The matching Processing library can do this periodically.)
- Attempting to read an array position that is out of bounds will print an error
  to the serial port and return the value -1.
- If a record contains too many values or too few, and an error is printed to
  the serial port. (The matching Processing library can relay this and other
  errors to the Processing console.)
- If a received line cannot be parsed as a series of integers, a warning is
  printed to the serial port.

## Installation

1. In the Arduino IDE, select the *Tools > Manager Libraries* menu item.
2. In the Arduino IDE, select the "Sketch > Include Library > Add .ZIP Library???"
   menu item. Select the downloaded ZIP file.
3. Click "Install".

![](docs/arduino-library-manager.png)

## Examples

Once you install the library, these examples are available in the *File >
Examples > SerialRecord* submenu. You can also review them [on
GitHub](https://github.com/osteele/Arduino_SerialRecord/tree/main/examples).

![](docs/arduino-examples.png)

### SendSingleValue

This sketch repeatedly sends a record that contains a single value.

The sketch pairs well with the ReceiveSingleValue example from the [Processing
SerialRecord] library.

You can also use the Serial Monitor to inspect the values that the sketch sends
to the serial port.

This sketch is no different from calling `Serial.println(value)`.

Things to try:

- Connect a potentiometer to the Arduino, and send its value instead.

### SendMultipleValues

This sketch repeatedly sends a record that contains two values:

- The first value is the value of `millis()`, modulo 32768.
- The second value is the analog value that is read from pin 9. If you attach a
  potentiometer to that pin, you can control this value by moving the pot.

This sketch pairs well with the RecieveMultipleValues example from the
[SerialRecord library for Processing 4] library.

You can also use the Serial Monitor to inspect the values that the sketch sends
to the serial port.

Things to try:

- Connect a second potentiometer to the Arduino, and send the values from
  both potentiometers.
- Send the value from another sensor, such as temperature or proximity.

### ReceiveSingleValue

This sketch repeatedly receives a record that contains a single value, and uses
it to control the builtin LED. The value should be 0 or 1.

This sketch pairs well with the SendSingleValue example from the [Processing
SerialRecord] library.

You can also interact with this sketch from the Serial Monitor. Enter `0` or `1`
into the text area at the top, and press "Send". Then enter `!e` to ask the
Arduino to send back the last values it received.

### ReceiveMultipleValues

This sketch repeatedly receives a record that contains two values. Both values
should be in the range 0???1023:

- The first value controls the builtin LED. The LED is turned on if the value is
  in the upper half of the range (512???1023).
- The second value controls a buzzer attached to pin 9. If the value is 0, the
  buzzer is silenced; otherwise, it plays a tone at the specified frequency.

This sketch pairs well with the SendMultipleValues example from the [Processing
SerialRecord] library.

You can also interact with this sketch from the Serial Monitor. Enter `100,200`
into the text area at the top, and press "Send". Then enter `!e` to ask the
Arduino to send back the last values it received.

### SendReceiveMultipleValues

This sketch repeatedly receives two values, and send back the same values in the
opposite order as well as their sum.

(This mode of communication, where a connection is used both to send and
receive, is called "full duplex".)

This sketch pairs well with the SendReceiveMultipleValues example from the
[SerialRecord library for Processing 4] library.

You can also interact with this sketch from the Serial Monitor. Enter `100,200`
into the text area at the top, and press "Send".

### SendFieldNames

This sketch is similar to SendMultipleValues, except that it also includes
field names in the strings that it sends. These are displayed in the Serial
Monitor and the Serial Console, but the [SerialRecord library for Processing 4] library
ignores them.

## Motivation

This library was intended as a replacement for the manual use of chains of:

```c++
Serial.print(value1);
Serial.print(",");
Serial.print(value2);
Serial.print(",");
Serial.print(value3);
Serial.println();
```

I found while teaching an introductory course physical on computing that novice
programmers often garble the order of values, commas and the newline when they
add, remove, or rearrange values. Debugging the resulting errors did not
contribute to the learning objectives for this particular course.

## Alternatives

For alternatives that support a variety of transports and serialization formats
(including higher-efficiency binary formats), browse the Communications topic of
the Arduino library manager. Also note
[Firmata](https://github.com/firmata/arduino), which features declarative
binding of value positions to sensors or pin numbers.

## Acknowledgements

The idea of providing this code as a library was inspired by code
provided to students by the NYU Shanghai IMA "Interaction Lab" course, for them to copy and paste into their sketches.

## License

Copyright (C) 2020-2022 Oliver Steele. This software is made available under the
terms of the GNU LGPL License.
