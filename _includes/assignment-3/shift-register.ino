#define OFF HIGH
#define ON LOW

// The pins to control which digit of the display to update,
// with index 0 being the one's spot (the rightmost digit).
const int displayPins[] = { 9, 10, 11, 12 };
// Tells us which segments to light up for each digit
const byte segments[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };

// Yellow: SRCLK
// Green: RCLK
// Blue: SER

const int dataPin = 4;   // SER
const int latchPin = 7;  // RCLCK
const int clockPin = 8;  // SRCLK

int pos = 0;
// int number = 25;
int startTimeSeconds;

// Display the digit on whichever display(s) are active.
// Pass -1 to blank the display.
void showDigit(byte digit) {
  byte bits;
  // 7 segment display is common anode, so we set the pin low
  // to turn on the segment.
  if (0 <= digit && digit <= 9) {
    bits = segments[digit] ^ 0xFF;
  } else {
    bits = 0xFF;
  }

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, bits);
  digitalWrite(latchPin, HIGH);
}

// Show a digit on the given display. Set digit = -1 to blank the display
void showDigitOn(byte digit, byte display) {
  for (byte i = 0; i < 4; i++) {
    digitalWrite(displayPins[i], i == display ? HIGH : LOW);
  }

  showDigit(digit);
}

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(displayPins[i], OUTPUT);
  }

  startTimeSeconds = millis() / 1000;
}

void loop() {
  byte number = millis() / 1000 - startTimeSeconds;
  number %= 60;

  if (pos == 0) {
    showDigitOn(number % 10, 0);
  } else {
    // Don't display the 10's digit for single digit numbers
    showDigitOn(number < 10 ? -1 : number / 10, 1);
  }

  pos = (pos + 1) % 2;
  delay(12);
}