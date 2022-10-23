/*
  SendReceiveMultipleValues

  This sketch repeatedly receives two values, and send back the same values in
  the opposite order as well as their sum.

  (This mode of communication, where a connection is used both to send and
  receive, is called "full duplex".)

  This sketch pairs well with the SendReceiveMultipleValues example from the
  Processing SerialRecord library
  <https://osteele.github.io/Processing_SerialRecord/>.

  You can also interact with this sketch from the Serial Monitor. Enter
  `100,200` into the text area at the top, and press "Send".

  by Oliver Steele, 2020-2022

  This example code is in the public domain.
*/

#include "SerialRecord.h"

SerialRecord reader(2);
SerialRecord writer(3);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (reader.read()) {
    int a = reader[0];
    int b = reader[1];

    writer[0] = b;
    writer[1] = a;
    writer[2] = a + b;
    writer.send();
  }
}
