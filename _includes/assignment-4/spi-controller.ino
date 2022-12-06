#include <SPI.h>

#define SCK_PIN  13
#define MISO_PIN 12
#define MOSI_PIN 11
#define SS_PIN   10

void setup() {
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(SS_PIN, OUTPUT);

  digitalWrite(SS_PIN, HIGH); 

  SPI.begin();
  Serial.begin(9600);

  digitalWrite(SS_PIN, LOW);  

  // The arduino seems to reboot right after sending, causing
  // the reader to print things twice.
  delay(1000);
  Serial.println("Sending...");
  send(" Nasser\n");
}

void transferAndWait(char what) {
  SPI.transfer(what);
  delayMicroseconds(20);
} 

void send(char *p) {
  while(*p) {
    transferAndWait(*p);
    p++;
    delay(20);
  }
}

void loop() {
}