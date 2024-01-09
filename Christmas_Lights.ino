/*
 * Christmas_Lights.ino
 * Software for custom christmas lights
 * Written by Quinn Neufeld
 * Dec. 8 2021
 * Dec. 23 2021 - Added DoubleSnake
 * Dec. 29 2022 - Added RandomOne, Removed unused `N_LIT_LEDS` definition
 * Dec. 30 2022 - Added RandomAll, fixed bug with DoubleSnake ending abruptly, replaced mode #definitions with Mode enum
 */

#include <FastLED.h>

#include "led_patterns/patternfactory.h"

#define DATA_PIN 2
#define N_LEDS 300

CRGB leds[N_LEDS];

LEDPatternFactory pattern_factory(leds, N_LEDS);

void clear_leds();

void setup() {
    randomSeed(analogRead(A0));

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, N_LEDS);
}

void loop() {
    Pattern pattern = (Pattern) random(1, 8);

    LEDPattern* running_pattern = pattern_factory.build_pattern(pattern);
    running_pattern->run();
    delete running_pattern;

    clear_leds();
}

// Cleanup LEDs
void clear_leds() {
    for (int i = 0; i < N_LEDS; i++) {
        leds[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
}
