#include "SerialRecord.h"

SerialRecord writer(2);

void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT);
}

void loop() {
  writer[3] = millis() % 32768;
  writer.send();

  delay(50);
}
