/*
 * Christmas_Lights.ino
 * Software for custom christmas lights
 * Written by Quinn Neufeld
 * Dec. 8 2021
 */

#include <FastLED.h>

#define DATA_PIN 2
#define N_LEDS 300
#define N_LIT_LEDS 50
#define UPDATE_DELAY 13

#define N_COLOURS floor(sizeof(COLOURS) / sizeof(CRGB))
static const CRGB COLOURS[2] = {
  CRGB(255, 0, 0),
  CRGB(0, 255, 0)
};

CRGB leds[N_LEDS];

int cur_led = 0;

int wrap(int, int, int);
void update_leds();
CRGB pick_colour();

void setup() {
  randomSeed(analogRead(A0));
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, N_LEDS);

  for (int i = cur_led; i < cur_led + N_LIT_LEDS; i++) {
    leds[i] = pick_colour();
  }
}

void loop() {
  unsigned long s_time = millis();
  
  update_leds();
  FastLED.show();
  cur_led = wrap(cur_led + 1, 0, N_LEDS);
  
  unsigned long e_time = millis();
  if ((e_time - s_time) < UPDATE_DELAY)
    delay(UPDATE_DELAY - (e_time - s_time));
}

// Updates the chain of lit LEDs
void update_leds() {
  //Clear last LED
  leds[wrap(cur_led, 0, N_LEDS)] = CRGB(0, 0, 0);
  //Set LED at the end of the chain
  leds[wrap(cur_led + N_LIT_LEDS, 0, N_LEDS)] = pick_colour();
}

// Returns a random colour from COLOURS
CRGB pick_colour() {
  return COLOURS[random(N_COLOURS)];
}

/*
 * Wraps a number around between s and e
 */
int wrap(int n, int s, int e) {
  return n % (e - s);
}
