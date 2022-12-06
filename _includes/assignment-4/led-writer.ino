const int emitterPin = 2;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  pinMode(emitterPin, OUTPUT);
}

void loop() {
  // Uncomment this to flash the LED for calibration.
  // digitalWrite(emitterPin, (millis() / 5000) % 2 ? HIGH : LOW);
  // return;

  if (Serial.available()) {
    byte input = Serial.read();
    transmit(input);
  }

  delay(100);
}

void transmit(byte value) {
  Serial.print("Sending ");
  Serial.print((char) value);
  Serial.print(" ");
  Serial.println(value);
  
  // Let the receiver know we're about to send
  digitalWrite(emitterPin, HIGH);
  delay(1000);

  for (byte i = 0; i < 8; i++) {
    digitalWrite(emitterPin, value & (1 << (7 - i)) ? HIGH : LOW);
    delay(1000);
  }

  digitalWrite(emitterPin, LOW);
}