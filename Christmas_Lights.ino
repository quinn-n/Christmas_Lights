/*
 * Christmas_Lights.ino
 * Software for custom christmas lights
 * Written by Quinn Neufeld
 * Dec. 8 2021
 * Dec. 23 2021 - Added DoubleSnake
 */

#include <FastLED.h>

#include "snake.h"
#include "overlapped_snake.h"
#include "double_snake.h"
#include "breathe.h"
#include "overlapped_breathe.h"

#define DATA_PIN 2
#define N_LEDS 300
#define N_LIT_LEDS 50

#define MODE_SNAKE 1
#define MODE_OVERLAPPED_SNAKE 2
#define MODE_DOUBLE_SNAKE 3
#define MODE_BREATHE 4
#define MODE_OVERLAPPED_BREATHE 5

CRGB leds[N_LEDS];

void clear_leds();

void setup() {
    randomSeed(analogRead(A0));

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, N_LEDS);
}

void loop() {
    int mode = random(1, 6);
    if (mode == MODE_SNAKE) {
        Snake* s = new Snake(leds, N_LEDS, random(1, 100), random(1, 3), random(15, 50), random(4, 10));
        s->snake();
        delete s;
    }
    else if (mode == MODE_OVERLAPPED_SNAKE) {
        OverlappedSnake* os = new OverlappedSnake(leds, N_LEDS, random(1, 3), random(15, 50), random(4, 10));
        os->overlapped_snake();
        delete os;
    }
    else if (mode == MODE_DOUBLE_SNAKE) {
        DoubleSnake* ds = new DoubleSnake(leds, N_LEDS, random(1, 50), random(15, 50), random(4, 10));
        ds->double_snake();
        delete ds;
    }
    else if (mode == MODE_BREATHE) {
        Breathe* b = new Breathe(leds, N_LEDS, random(5000, 20000), random(3, 8));
        b->breathe();
        delete b;
    }
    else if (mode == MODE_OVERLAPPED_BREATHE) {
        OverlappedBreathe* ob = new OverlappedBreathe(leds, N_LEDS, random(5000, 20000), random(3, 8));
        ob->overlapped_breathe();
        delete ob;
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
