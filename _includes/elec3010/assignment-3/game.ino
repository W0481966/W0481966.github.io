/* The player's goal is to make it to the hole. */

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Animate the player character with these frames
byte frames[][8] = {
  {
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b00100,
    0b00010,
    0b00001
  }, {
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b00100,
    0b00100,
    0b00100
  }, {
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b00100,
    0b01000,
    0b10000
  }, {
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b00100,
    0b00100,
    0b00100
  }
};

const int numFrames = 4;

byte hole[] = {
  0b00000,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00000,
  0b00000
};

// Voltages for each button.
const int buttonValues[] = {1023, 740, 504, 327, 143, 0};
const int btnNone = 0;
const int btnSelect = 1;
const int btnLeft = 2;
const int btnDown = 3;
const int btnUp = 4;
const int btnRight = 5;

// 5 bit values. The lower 4 bits store the object's column, and the
// 5th bit stores the row.
int playerPos;
int holePos;

// Increments on each iteration of loop()
int counter = 0;

// Read a button value from A0
int _getButton() {
  int value = analogRead(A0);

  for (int i = 0; i < 6; i++) {
    if (abs(buttonValues[i] - value) <= 10) return i;
  }

  // Should never reach here
  return -1;
}

// Read and debounce a button value
int getButton() {
  int value1 = _getButton();
  if (value1 == btnNone) return btnNone;
  delay(10);

  int value2 = _getButton();
  // If value2 != value1, it could be the start of a different
  // button press, so we start over.
  return value1 == value2 ? value1 : getButton();
}

// The display is upside-down relative to the buttons, so the
// button labeled down is actually above the button labeled up.
// So we treat them as the opposite of what they're labeled.
void handleUp() {
  if (!(playerPos & 1 << 4)) {
    lcd.setCursor(playerPos & 0b1111, 0);
    lcd.print(" ");
    playerPos = playerPos | 0b10000;
  }
}

void handleDown() {
  if (playerPos & 1 << 4) {
    lcd.setCursor(playerPos & 0b1111, 1);
    lcd.print(" ");
    playerPos = playerPos & 0b01111;
  }
}

// Left and right are similarly reversed.
void handleLeft() {
  if ((playerPos & 0b1111) != 15) {
    lcd.setCursor(playerPos & 0b1111, playerPos >> 4);
    lcd.print(" ");
    playerPos++;
  }
}

void handleRight() {
  if ((playerPos & 0b1111) != 0) {
    lcd.setCursor(playerPos & 0b1111, playerPos >> 4);
    lcd.print(" ");
    playerPos--;
  }
}

void drawObject(int pos, bool isPlayer) {
  lcd.setCursor(pos & 0b1111, pos >> 4);
  lcd.write(isPlayer ? counter % 4 + 1 : numFrames + 1);
}

void setup() {
  randomSeed(analogRead(A1));

  lcd.begin(16, 2);
  for (int f = 0; f < numFrames; f++) lcd.createChar(f + 1, frames[f]);
  lcd.createChar(numFrames + 1, hole);

  playerPos = random(31);
  do {
    holePos = random(31);
  } while (holePos == playerPos);

  drawObject(holePos, false);
}

void loop() {
  int button = getButton();
  if (button == btnUp) handleUp();
  else if (button == btnDown) handleDown();
  else if (button == btnRight) handleRight();
  else if (button == btnLeft) handleLeft();

  if (playerPos == holePos) {
    lcd.setCursor(0, 0);
    lcd.print("    You win!    ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
  } else {
    drawObject(playerPos, true);
  }

  counter = (counter + 1) % 4;
  delay(100);
}