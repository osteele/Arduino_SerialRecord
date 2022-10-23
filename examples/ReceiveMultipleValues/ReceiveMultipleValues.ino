/*
  ReceiveMultipleValues

  This sketch repeatedly receives a record that contains a single value, and
  uses it to control the builtin LED. The value should be 0 or 1.

  This sketch pairs well with the SendSingleValue example from the Processing
  SerialRecord library <https://osteele.github.io/Processing_SerialRecord/>.

  You can also interact with this sketch from the Serial Monitor. Enter
  `100,200` into the text area at the top, and press "Send". Then enter `!e` to
  ask the Arduino to send back the last values it received.

  by Oliver Steele, 2020-2022

  This example code is in the public domain.
*/

#include "SerialRecord.h"

// Change this number to the number of values you want to receive
SerialRecord reader(2);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  reader.read();

  if (reader[0] > 512) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  tone(9, reader[1]);
}
