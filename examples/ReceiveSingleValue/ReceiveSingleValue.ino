/*
  ReceiveSingleValue

  This sketch repeatedly receives a record that contains two values. Both values
  should be in the range 0…1023:

  - The first value controls the builtin LED. The LED is turned on if the value
    is in the upper half of the range (512…1023).
  - The second value controls a buzzer attached to pin 9. If the value is 0, the
    buzzer is silenced; otherwise, it plays a tone at the specified frequency.

  This sketch pairs well with the SendMultipleValues example from the
  Processing SerialRecord library
  <https://osteele.github.io/Processing_SerialRecord/>.

  You can also interact with this sketch from the Serial Monitor. Enter `0` or
  `1` into the text area at the top, and press "Send". Then enter `!e` to
  ask the Arduino to send back the last values it received.

  by Oliver Steele, 2020-2022

  This example code is in the public domain.
*/

#include "SerialRecord.h"

SerialRecord reader(1);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  reader.read();
  digitalWrite(LED_BUILTIN, reader[0]);
}
