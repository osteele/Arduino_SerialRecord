/*
  SendMultipleValues

  This sketch repeatedly sends a record that contains two values:

  - The first value is the value of `millis()`, modulo 32768.
  - The second value is the analog value that is read from pin 9. If you attach
    a potentiometer to that pin, you can control this value by moving the pot.

  This sketch pairs well with the RecieveMultipleValues example from the
  Processing SerialRecord library
  <https://osteele.github.io/Processing_SerialRecord/>.

  Things to try:
  - Connect a second potentiometer to the Arduino, and send the values from both
    potentiometers.
  - Send the value from another sensor, such as temperature or proximity.

  by Oliver Steele, 2020-2022

  This example code is in the public domain.
*/

#include "SerialRecord.h"

// Change this number to send a different number of values
SerialRecord writer(2);

void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT);
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
