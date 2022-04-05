/*
  SendSingleValue

  This sketch repeatedly sends a record that contains a single value. The value
  is the value of `millis()`, modulo 32768.

  This sketch pairs well with the ReceiveSingleValue example from the
  [Processing SerialRecord] library.

  You can also use the Serial Monitor to inspect the values that the sketch
  sends to the serial port.

  Things to try:
  - Connect a potentiometer to the Arduino, and send its value instead.

  by Oliver Steele, 2020-2022

  This example code is in the public domain.
*/

#include "SerialRecord.h"

SerialRecord writer;

void setup() { Serial.begin(9600); }

void loop() {
  int value = millis() % 32768;
  writer.send(value);

  // This delay slows down the loop. The connected computer can become sluggish
  // if it has to receive data at too high a rate.
  delay(50);
}
