#include <LiquidCrystal.h>

const int pinRS = 8;
const int pinEN = 9;
const int pinD4 = 4;
const int pinD5 = 5;
const int pinD6 = 6;
const int pinD7 = 7;
const int pinBL = 10;
LiquidCrystal lcd(pinRS, pinEN, pinD4, pinD5, pinD6, pinD7);

// Discovered this experimentally. It doesn't match anything I found online.
// Left and select simply don't have any effect, so they're omitted.
const int buttonValues[] = { 505, 328, 145, 0 };
const char* buttonStrings[] = { "None", "Down", "Up", "Right" };
const int btnNone = 0;
const int btnDown = 1;
const int btnUp = 2;
const int btnRight = 3;

int total = 0;
int prevButton = btnNone;

int _detectButton() {
  int signal = analogRead(A0);

  for (int value = 0; value < 4; value++) {
    if (abs(buttonValues[value] - signal) <= 10) return value;
  }

  // Well, this should never happen, but just in case...
  return -1;
}

int detectButton() {
  int button1 = _detectButton();
  if (button1 == btnNone) return btnNone;

  // Debounce
  delay(10);
  int button2 = _detectButton();

  // If button1 != button2, it's possible that it's the start of a legitimate
  // button press, so we restart the debounce check. Probably better to do it
  // as a loop, but this way is good enough for this assignment.
  return button1 == button2 ? button1 : detectButton();
}

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Total:");
  lcd.setCursor(0, 1);
  lcd.print("$");
}

void loop() {
  int buttonSignal = analogRead(A0);

  int button = detectButton();
  if (button != prevButton) {
    if (button == btnDown) total += 100;
    else if (button == btnUp) total += 25;

    prevButton = button;
  }

  // Start at 1 to preserve the $ sign in position 0
  lcd.setCursor(1, 1);
  lcd.print("               ");
  lcd.setCursor(1, 1);
  // Yeah, I could just use a double, but that's boring. Besides, you
  // never use floats with financial data.
  int dollars = total / 100;
  int cents = total % 100;
  lcd.print(dollars);
  lcd.print(".");
  if (cents < 10) lcd.print("0");
  lcd.print(cents);

  delay(30);
}
