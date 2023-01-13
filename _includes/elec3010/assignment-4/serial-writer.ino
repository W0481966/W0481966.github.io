#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // RX, TX

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  Serial.println("Goodnight moon!");

  mySerial.begin(4800);
  mySerial.println("Hello, world?");
}

void loop() {
  // if (mySerial.available()) {
  //   Serial.write(mySerial.read());
  // }
  if (Serial.available()) {
    mySerial.print("From Uno: ");
    while (Serial.available()) {
      mySerial.write(Serial.read());
    }
    mySerial.print("\n");
  }
}