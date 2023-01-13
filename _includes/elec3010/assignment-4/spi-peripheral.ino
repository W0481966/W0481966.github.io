/* 10 - 53
 * 11 - 51
 * 12 - 50
 * 13 - 52 */

#include <SPI.h>

bool received = false;
byte slaveReceived;

byte readPos = 31;
byte writePos = 31;
char buffer[32];

void setup() {
  Serial.begin(9600);

  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

ISR (SPI_STC_vect) {
  byte rec = SPDR;
  if (rec == 0xFF) return;
  Serial.print((char) rec);
}

void loop() {
}