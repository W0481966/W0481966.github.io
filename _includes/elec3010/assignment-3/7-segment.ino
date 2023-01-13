// Current goes from the digit pin, through the LED, and out
// each segment pin. So setting a segment pin to HIGH will turn
// it off, since the voltages will cancel out. This makes things
// less confusing.
#define OFF HIGH
#define ON LOW

// The pins to control segments. Index 0 = A, 1 = B, ... 7 = DP
const int segmentPins[] = { 11, 7, 4, 2, 1, 10, 5, 3 };
// The pins to control which digit of the display to update,
// with index 0 being the one's spot (the rightmost digit).
const int digitPins[] = { 6, 8, 9, 12 };
// Tells us which segments to light up for each digit
const int segments[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };

/* Choose which 7-segment display showDigit() alters.
 * Pass -1 to disable them all. */
void selectDisplay(int pos) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], pos == i ? HIGH : LOW);
  }
}

/* Display a digit on the selected 7-segment display.
 * Pass -1 to blank the display. */
void showDigit(int digit) {
  if (0 <= digit && digit <= 9) {
    int bits = segments[digit];
    
    for (int s = 0; s < 8; s++) {
      digitalWrite(segmentPins[s], bits & (1 << s) ? ON : OFF);
    }
  } else {
    for (int s = 0; s < 8; s++) {
      digitalWrite(segmentPins[s], OFF);
    }
  }
}

/* Display a a digit on the provided 7-segment display. All calls
 * to showDigit() will update the given display until this or
 * selectDisplay() are called.
 * Set digit = -1 to blank the display. */
void showDigitOn(int digit, int display) {
  selectDisplay(display);
  showDigit(digit);
}

void setup() {
  for (int i = 0; i < 4; i++) pinMode(digitPins[i], OUTPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], OFF);
  }

  selectDisplay(0);
  for (int digit = 0; digit < 10; digit++) {
    showDigitOn(digit, 3);
    delay(1000);
  }

  showDigitOn(-1, 3);
}
void loop() {
}