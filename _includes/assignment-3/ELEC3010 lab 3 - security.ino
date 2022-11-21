#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const byte numKeyRows = 4;
const byte numKeyCols = 4;
char keys[numKeyRows][numKeyCols]{
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

const byte rowPins[] = { 9, 8, 7, 6 };
const byte colPins[] = { 5, 4, 3, 2 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, numKeyRows, numKeyCols);

const int redPin = 12;
const int greenPin = 13;

int answer;
int input = 0;
byte pressCount = 0;

void handleKeypress(char key) {  
  switch (key) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      if (pressCount == 0) {
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, LOW);
        lcd.setCursor(0, 1);
        lcd.print("                ");
      }
      input = input * 10 + key - '0';
      pressCount++;
      break;
  }
}

/* Zero-pads the number to the desired number of digits.
 * Be careful! If the number has more digits than numDigits, the
 * extra digits will be omitted from the output.
 *
 * We can get the nth digit of a number with this formula:
 *   digit = (number / (10^(n-1))) % 10
 * The division essentially digit-shifts (like bit-shifting, but
 * in base 10) the number n-1 places to the right, and the
 * modulus strips off any digits left of what we want. */
void printNumber(int number, byte numDigits) {
  long tens = 1;
  for (byte i = 0; i < numDigits - 1; i++) tens *= 10;

  for (; tens >= 1; tens /= 10) lcd.print((number / tens) % 10);
}

void setup() {
  randomSeed(analogRead(A1));
  answer = random(9999);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Code: ");
  printNumber(answer, 4);
}

void loop() {
  char key = keypad.waitForKey();
  handleKeypress(key);

  lcd.setCursor(0, 1);
  printNumber(input, pressCount);

  if (pressCount == 4) {
    if (input == answer) {
      lcd.print(" Correct");
      digitalWrite(greenPin, HIGH);
    } else {
      lcd.print(" Incorrect");
      digitalWrite(redPin, HIGH);
    }
    pressCount = 0;
    input = 0;
  }
}