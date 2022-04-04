/*
  Example of use of the SerialRecord libray to send multiple values between the
  Arduino and the Arduino IDE, a Processing Sketch, or another application
  connected to the other end of the serial connection.

  Copyright (C) 2020-2022 Oliver Steele

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SerialRecord.h"

// Change this number to the number of values you want to receive
SerialRecord reader(2);

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  reader.read();

  // add your code here
  // use elements in the values array
  // values[0]
  // values[1]
  if (reader.values[0] > 512) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  if (reader.values[1] == 1) {
    tone(9, reader.values[2]);
  } else {
    noTone(9);
  }
}
