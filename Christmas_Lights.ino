/*
 * Christmas_Lights.ino
 * Software for custom christmas lights
 * Written by Quinn Neufeld
 * Dec. 8 2021
 */

#include <FastLED.h>

#include "snake.h"
#include "breathe.h"

#define DATA_PIN 2
#define N_LEDS 300
#define N_LIT_LEDS 50

#define MODE_SNAKE 1
#define MODE_BREATHE 2

CRGB leds[N_LEDS];

void clear_leds();

void setup() {
    randomSeed(analogRead(A0));

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, N_LEDS);
}

void loop() {
    int mode = random(1, 3);
    if (mode == MODE_SNAKE) {
        Snake* s = new Snake(leds, N_LEDS, random(1, 100), random(15, 50), random(1, 5));
        s->snake();
        delete s;
    }
    else if (mode == MODE_BREATHE) {
        Breathe* b = new Breathe(leds, N_LEDS, random(5000, 20000), random(2, 5));
        b->breathe();
        delete b;
    }
    clear_leds();
}

// Cleanup LEDs
void clear_leds() {
    for (int i = 0; i < N_LEDS; i++) {
        leds[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
}
