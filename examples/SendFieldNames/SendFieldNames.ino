/*
  SendMFieldNames

  Reads an analog input on pin 0, and sends a record that contains two values:

  1. Value of `millis()`, modulo 1024.
  2. The analog value that is read from pin 0.

  If you attach a potentiometer to pin 0, you can control this value by moving
  the pot.

  This sketch is similar to SendMultipleValues, except that it also includes
  field names in the strings that it sends. These are displayed in the Serial
  Monitor and the Serial Console. The Processing SerialRecord library
  <https://osteele.github.io/Processing_SerialRecord/> igonores them.

  by Oliver Steele, 2020-2022

  This example code is in the public domain.
*/

#include "SerialRecord.h"

// Change this number to send a different number of values
SerialRecord writer(2);

void setup() {
  Serial.begin(9600);

  writer.setFieldName(0, "millis");
  writer.setFieldName(1, "analog");
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
