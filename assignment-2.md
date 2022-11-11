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

[RGB LED](/assets/assignment-2/ELEC3010 lab 2 - rgb led.mp4)
