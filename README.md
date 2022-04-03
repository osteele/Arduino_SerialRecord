# Serial Record Library for Arduino

Library to send and read single or multiple values to and from the serial port.

The library transmits the values in ASCII. Each record is a sequence of ASCII
representations of numbers, separated by a comma and terminated by a newline.
This is the format used by the Arduino IDE Serial Plotter tool.

## Design Goals

- Easy for novice programmers to configure and use
- Easy to inspect the transmitted data
- Detects and provides diagnostics for common errors

### Non-goals

- Efficiency. This use ASCII, which is easy to inspect but computationally expensive to
  read and write, and requires more bandwidth than a binary representation.
- Flexibility. All records must have the same number of values. This makes it
  possible to detect errors in code that uses the library, but is not
  appropriate to all communications. If you need more flexibility, this is not
  the library for you. (See the Alternatives section below.)

## Installation

1. Download a ZIP archive of this repository: Click on the green Code button at
   the top of this page, and press "Download ZIP".
2. In the Arduino IDE, select the "Sketch > Include Library > Add .ZIP Library…"
   menu item, and select the downloaded ZIP file.

If you can't find the downloaded zip file but you can instead find a folder with
the same name, your computer may be set to automatically decompress and delete
downloaded ZIP files. In that case, instead of step 2 you can move the folder
into the Arduino/Libraries folder in your home directory, and then restart the
Arduino IDE.

## Motivation

This was intended as a replacement for the manual use of chains of:

```c++
Serial.print(value1);
Serial.print(",");
Serial.print(value2);
Serial.print(",");
Serial.print(value3);
Serial.println();
```

I found while teaching an introductory course physical on computing that novice
programmers often garbled the order of values and commas when they added,
removed, or rearranged value, and that debugging the resulting errors did not
contribute to the learning objectives for this particular course. (The problem
is even worse when they work from example code that optimizes for line count,
such that the last two lines are combined to `Serial.print(value3);`.)

## Features

- Send an 'e' to the sketch to send received the values array back to the serial
  port.
- Attempting to read an array position that is out of bounds will print an error
  to the serial port and return the value -1.
- If a record contains too many values, it is ignored, and an error is printed
  to the serial port.

## Alternatives

For alternatives that support a variety of transports and serialization formats
(including higher-efficiency binary formats), browse the Communications topic of
the Arduino library manager. Also note
[Firmata](https://github.com/firmata/arduino), which features declarative
binding of value positions to sensors or pin numbers.

## Acknowledgements

The idea of providing this code as a library was inspired by copy-paste code
provided to students by the NYU Shanghai IMA "Interaction Lab" course.

## License

Copyright (C) 2020-2022 Oliver Steele. This software is made available under the
terms of the GNU LGPL License.
