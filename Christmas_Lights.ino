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

#include "snake.h"
#include "overlapped_snake.h"
#include "double_snake.h"
#include "breathe.h"
#include "overlapped_breathe.h"
#include "random_one.h"
#include "random_all.h"

#define DATA_PIN 2
#define N_LEDS 300

enum class Mode {
    Snake = 1,
    OverlappedSnake = 2,
    DoubleSnake = 3,
    Breathe = 4,
    OverlappedBreathe = 5,
    RandomOne = 6,
    RandomAll = 7
};

CRGB leds[N_LEDS];

void clear_leds();

void setup() {
    randomSeed(analogRead(A0));

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, N_LEDS);
}

void loop() {
    Mode mode = (Mode) random(1, 8);
    if (mode == Mode::Snake) {
        Snake* s = new Snake(leds, N_LEDS, random(1, 100), random(1, 3), random(15, 50), random(4, 10));
        s->snake();
        delete s;
    }
    else if (mode == Mode::OverlappedSnake) {
        OverlappedSnake* os = new OverlappedSnake(leds, N_LEDS, random(1, 3), random(15, 50), random(4, 10));
        os->overlapped_snake();
        delete os;
    }
    else if (mode == Mode::DoubleSnake) {
        DoubleSnake* ds = new DoubleSnake(leds, N_LEDS, random(10, 50), random(15, 50), random(4, 10));
        ds->double_snake();
        delete ds;
    }
    else if (mode == Mode::Breathe) {
        Breathe* b = new Breathe(leds, N_LEDS, random(5000, 20000), random(3, 8));
        b->breathe();
        delete b;
    }
    else if (mode == Mode::OverlappedBreathe) {
        OverlappedBreathe* ob = new OverlappedBreathe(leds, N_LEDS, random(5000, 20000), random(3, 8));
        ob->overlapped_breathe();
        delete ob;
    }
    else if (mode == Mode::RandomOne) {
        RandomOne* ro = new RandomOne(leds, N_LEDS, random(100, 200), random(300, 450));
        ro->random_one();
        delete ro;
    }
    else if (mode == Mode::RandomAll) {
        RandomAll* ra = new RandomAll(leds, N_LEDS, random(150, 500), random(4, 10));
        ra->random_all();
        delete ra;
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
