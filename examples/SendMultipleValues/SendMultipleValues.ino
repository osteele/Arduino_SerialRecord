/*
  SendMultipleValues

  Reads an analog input on pin 0, and sends a record that contains two values:

  1. Value of `millis()`, modulo 1024.
  2. The analog value that is read from pin 0.

  If you attach a potentiometer to pin 0, you can control this value by moving
  the pot.

  This sketch pairs well with the RecieveMultipleValues example from the
  Processing SerialRecord library
  <https://osteele.github.io/Processing_SerialRecord/>.

  Things to try:
  - Connect a second potentiometer to the Arduino, and send the values from both
    potentiometers, instead of send a value that is based on `millis()`.
  - Send the value from another sensor, such as temperature or proximity.

  by Oliver Steele, 2020-2022

  This example code is in the public domain.
*/

#include "SerialRecord.h"

// Change this number to send a different number of values
SerialRecord writer(2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);

  writer[0] = millis() % 1024;
  writer[1] = sensorValue;
  writer.send();

  // This delay slows down the loop, so that it runs less frequently. This
  // prevents it from sending data faster than a Processing sketch that runs at
  // 60 frames per second will process it. It also makes it easier to debug the
  // sketch, because values are received at a slower rate.
  delay(20);
}
