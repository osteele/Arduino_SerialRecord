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

SerialValueReader reader;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  reader.getSerialData();
  digitalWrite(13, reader.value);
}
