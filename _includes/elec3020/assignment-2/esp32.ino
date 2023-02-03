#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>

// Defines SSID and PASSWORD - unversioned
#include "login.h"
char *ssid = SSID;
char *wifiPassword = PASSWORD;

char *cayenneUsername = "ca13a9c0-9808-11ed-b193-d9789b2af62b";
char *cayennePassword = "b73e5ae6edcdb8741b88a1488fa5e508e393a9ab";
char *cayenneClientId = "347ecc00-983f-11ed-b193-d9789b2af62b";

#define LCD_CHANNEL 6

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial to be available

  lcd.init();
  lcd.backlight();

  Cayenne.begin(cayenneUsername, cayennePassword, cayenneClientId, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
}

CAYENNE_IN(LCD_CHANNEL) {
  Serial.println("LCD receieved");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(getValue.asInt());
}