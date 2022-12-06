#include <SPI.h>

const int dataOut = 11; // COPI
const int dataIn = 12; // CIPO
const int SPIClock = 13;
const int ChipSelect = 10;

const int opWREN = 6;
const int opWRDI = 4;
const int opRDSR = 5;
const int opWRSR = 1;
const int opREAD = 3;
const int opWRITE = 2;

void setup() {
  Serial.begin(9600);
  
}