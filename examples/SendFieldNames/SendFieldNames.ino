/*
  SendMFieldNames

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
  pinMode(6, INPUT);

  writer.setFieldName(0, "millis");
  writer.setFieldName(1, "analog");
}

void loop() {
  int sensorValue = analogRead(6);

  writer[0] = millis() % 1024;
  writer[1] = sensorValue;
  writer.send();

  // This delay slows down the loop. This can make it easier to debug the
  // program.
  delay(10);
}
