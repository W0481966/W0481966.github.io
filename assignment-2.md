---
layout: page
title: "Assignment 2"
permalink: /assignment-2
---

# Assignment 2

## Back and forth LEDs

[Watch video](/assets/assignment-2/ELEC3010 lab 2 - back and forth.mp4)


```c
const int NUM_LEDS = 10;
// You can't upload to the Arduino if you wire in the first
// two pins (which are RX and TX), so we start from 2.
const int PIN_OFFSET = 2;  // The first pin
const int MAX_PIN = NUM_LEDS + PIN_OFFSET - 1;
const int DELAY = 100;

int step = 0;

void setup() {
  for (int pin = PIN_OFFSET; pin < NUM_LEDS + PIN_OFFSET; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, 0);
  }
}

/* Oh, you'll rue the day you asked us to see how few lines we
 * could use! Can you handle THE GLORY?! Mwahahahahahahahahahaaaaa!
 */
void loop() {
  for (int part = 0; part < 2; part++) digitalWrite(pinFromStep(part ? step = (step + 1) % (NUM_LEDS * 2 - 2) : step), part);
  delay(DELAY);
}

/* Here's something I might use in real life, following the same
 * logic as above. First we turn off the LED for the current step,
 * then we advance to the next step, then turn on the LED for the
 * new step. */
void legible_loop() {
  int pin = pinFromStep(step);
  digitalWrite(pin, 0);
  step = (step + 1) % (NUM_LEDS * 2 - 2);
  pin = pinFromStep(step);
  digitalWrite(pin, 1);
  delay(DELAY);
}

/* There are NUM_LEDS * 2 - 2 steps for the cycle. Each middle LED
 * lights twice per cycle - once going left, and once going right.
 * The two LEDs on the end only light once per cycle. That gives us
 * NUM_LEDS * 2 - 2 steps in the cycle. If we number each step
 * from 0 to NUM_LEDS * 2 - 3, this function gives us the pin of
 * LED to light for that step.
 *
 * The trick here is to note that if you create a function p(s)
 * that maps the step to the pin, the graph is a reflection and
 * translation of y = |x|. */
int pinFromStep(int step) {
  return MAX_PIN - abs(step - (NUM_LEDS - 1));
}
```

## Debounce button

[Watch video](/assets/assignment-2/ELEC3010 lab 2 - debounce.webm)

```c
const int debounceDelay = 10;
const int pushButton = 2;
int state = 0;
int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
}

void loop() {
  int newState1 = digitalRead(pushButton);

  if (newState1 != state) {
    delay(debounceDelay);
    int newState2 = digitalRead(pushButton);

    if (newState2 == newState1) {
      state = newState1;

      if (state == 1) {
        count++;
        // Tempting to include stdio.h and sprintf() this
        Serial.print("You've pressed the button ");
        Serial.print(count);
        Serial.println(" times.");
      }
    }
  }

  delay(1);  // delay in between reads for stability
}
```

## Variable blink rate

[Watch video](/assets/assignment-2/ELEC3010 lab 2 - variable blink.mp4)

```c
const int ledPin = 13;
const int potPin = A0;

int led = 0;
int ledDuration = -1;
int lastLedChangeTime = -100000;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(ledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int potValue = analogRead(potPin);
  int ledDuration = map(potValue, 0, 1023, 1000, 50);
  int elapsed = millis();
  
  if (elapsed - lastLedChangeTime >= ledDuration) {
    led = !led;
    digitalWrite(ledPin, led ? HIGH : LOW);
    lastLedChangeTime = elapsed;
  }

  delay(1);
}
```

## Nightlight

[Watch video](/assets/assignment-2/ELEC3010 lab 2 - photoresistor.mp4)

```c
const int ledPin = 9;
const int photoResPin = A0;

// Measured minimum and maximum values
const int lightMin = 10;
const int lightMax = 446;
const int lightThreshold = (lightMin + lightMax) / 2;
// The amount to increase or decrease LED luminence per iteration
const int lightDelta = 8;

// LED luminence, from 0-255
int ledValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int lightValue = analogRead(photoResPin);

  if (lightValue < lightThreshold) {
    ledValue += lightDelta;
    if (ledValue > 255) ledValue = 255;
  } else {
    ledValue -= lightDelta;
    if (ledValue < 0) ledValue = 0;
  }

  analogWrite(ledPin, ledValue);
  delay(100);
}
```

## RGB LED

[Watch video](/assets/assignment-2/ELEC3010 lab 2 - rgb led.mp4)

```c
const int buttonPin = 2;
const int debounceDelay = 10;
// 0 is released, 1 is pressed
int buttonState = 0;

const int potPin = A0;

/* Index 0 = red, 1 = green, 2 = blue.
 * By constructing it like this, we can easily switch between
 * colors with modular arithmetic. */
const int colorPins[] = {11, 9, 10};
int color[] = {0, 0, 0};
// This tells us which color component to change.
int colorIndex = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  for (int i = 0; i < 3; i++) pinMode(colorPins[i], OUTPUT);
}

void loop() {
  pollButton(cycleColor, NULL);

  int colorComponentLevel = map(analogRead(potPin), 0, 1023, 0, 255);
  color[colorIndex] = colorComponentLevel;

  // Display the color
  for (int i = 0; i < 3; i++) {
    analogWrite(colorPins[i], color[i]);
  }

  delay(1);
}

/* Move to the next color component: R -> G, G -> B, B -> R. */
void cycleColor() {
  colorIndex = (colorIndex + 1) % 3;
}

/* If the button has actually been pressed or released, we call the
 * appropriate function. Pass null if you don't want to execute
 * anything on that event. Uses a debounce check to ensure that the
 * button was pressed. */
void pollButton(void (*onPress)(void), void (*onRelease)(void)) {
  int curButtonState = digitalRead(buttonPin);

  if (curButtonState != buttonState) {
    delay(debounceDelay);
    int curButtonState2 = digitalRead(buttonPin);

    if (curButtonState2 == curButtonState) {
      buttonState = curButtonState;

      if (buttonState == 0) {
        if (onRelease) (*onRelease)();
      } else {
        if (onPress) (*onPress)();
      }
    }
  }
}
```
