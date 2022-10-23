/*
  SendSingleValue

  This sketch repeatedly sends a record that contains a single value. The value
  is the value of `millis()`, modulo 32768.

  This sketch pairs well with the ReceiveSingleValue example from the
  Processing SerialRecord library
  <https://osteele.github.io/Processing_SerialRecord/>.

  You can also use the Serial Monitor to inspect the values that the sketch
  sends to the serial port.

  Things to try:
  - Connect a potentiometer to the Arduino, and send its value instead.

  by Oliver Steele, 2020-2022

  This example code is in the public domain.
*/

#include "SerialRecord.h"

SerialRecord writer(1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = millis() % 1024;
  writer[0] = value;
  writer.send();

  // This delay slows down the loop. This can make it easier to debug the
  // program.
  delay(10);
}
