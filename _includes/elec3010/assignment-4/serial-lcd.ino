#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
byte pos = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello");

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    lcd.setCursor(pos &0xF, pos >> 4);
    lcd.print((char) Serial.read());
    pos = (pos + 1) % 32;
  }
}
