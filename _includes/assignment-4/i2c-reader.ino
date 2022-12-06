#include <Wire.h>

const int id = 4;

void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("Setup complete");
}

void loop() {
  delay(100);
}

void receiveEvent() {
  while (1 < Wire.available()) {
    Serial.print((char) Wire.read());
  }
  
  Serial.println((int) Wire.read());
}