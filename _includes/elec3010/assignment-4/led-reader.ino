const int sensorNeg = 2;
const int sensorPos = 3;

bool receiving = false;
byte bitsReceived = 0;
byte value = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Ready");
}

void loop() {
  // Milliseconds aren't as precise as I'd like, but delayMicroSeconds() has
  // some limitations that make it impractical for this.
  unsigned long startTime = millis();

  bool seeingLight = checkForLight();
  // Serial.print("Light is ");
  // Serial.println(seeingLight ? "on" : "off");

  if (receiving) {
    value = value << 1;
    if (seeingLight) value++;
    bitsReceived++;

    if (bitsReceived == 8) {
      Serial.print("Value: ");
      Serial.print((char) value);
      Serial.print(" ");
      Serial.println(value);

      receiving = false;
      bitsReceived = 0;
      // Don't need to reset value, since its bits will be shifted out anyway.
    }
  } else {
    if (seeingLight) receiving = true;
  }

  // Serial.println(count);
  unsigned long endTime = millis();
  unsigned long elapsedTime = endTime - startTime;
  delay(1000 - elapsedTime);
}

// This function takes ~115ms
bool checkForLight() {
  unsigned long count;

  pinMode(sensorNeg, OUTPUT);
  pinMode(sensorPos, OUTPUT);
  digitalWrite(sensorNeg, HIGH);
  digitalWrite(sensorPos, LOW);

  pinMode(sensorNeg, INPUT);
  digitalWrite(sensorNeg, LOW);

  for (count = 0; count < 100000; count++) {
    if (digitalRead(sensorNeg) == 0) break;
  }

  // Uncomment this for calibration
  // Serial.print("Count: ");
  // Serial.println(count);

  // FIXME: Add some calibration code instead of hard-coding this, so that
  // we don't have to recompile if the environment changes.
  return count < 90000;
}