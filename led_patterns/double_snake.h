
/*
 * double_snake.h
 * Displays two snakes that pass each other on alternating LEDs
 * Written by Quinn Neufeld
 * Dec. 23 2021
 */

#ifndef DOUBLE_SNAKE_H
#define DOUBLE_SNAKE_H

#include <FastLED.h>

#include "snake.h"
#include "ledpattern.h"

class DoubleSnake : public LEDPattern {
    public:
    DoubleSnake(CRGB* leds, int n_leds, int n_lit_leds, int tick_delay, int times) {
        this->leds = leds;
        this->n_leds = n_leds;
        this->n_lit_leds = n_lit_leds;
        this->tick_delay = tick_delay;
        this->times = times;
    }
    void run() {
        int primary_col_id = random(SNAKE_N_COLOURS);
        const CRGB* primary_colour = &SNAKE_COLOURS[primary_col_id];
        const CRGB* secondary_colour = NULL;
        if (primary_col_id == 0) {
            secondary_colour = &SNAKE_COLOURS[1];
        } else if (primary_col_id == 1) {
            secondary_colour = &SNAKE_COLOURS[0];
        }
        for (int t = 0; t < times; t++) {
            for (int i = 0; i < n_leds; i+= 2) {
                update_primary_snake(i, primary_colour);
                update_secondary_snake(i, secondary_colour);
                FastLED.show();
                tick();
            }
        }
        for (int i = 0; i < n_lit_leds * 2; i += 2) {
            close_primary_snake(i);
            close_secondary_snake(i);
            FastLED.show();
            tick();
        }
    }
    private:
    CRGB* leds;
    int n_leds;
    int n_lit_leds;
    int tick_delay;
    int times;

    void update_primary_snake(int led, const CRGB* colour) {
        leds[led] = *colour;
        leds[wrap(led - n_lit_leds * 2, 0, n_leds)] = CRGB(0, 0, 0);
    }

    void update_secondary_snake(int led, const CRGB* colour) {
        int sec_led = n_leds - led - 1;
        leds[sec_led] = *colour;
        leds[wrap(sec_led + n_lit_leds * 2, 0, n_leds)] = CRGB(0, 0, 0);
    }

    void close_primary_snake(int led) {
        leds[wrap(led - n_lit_leds * 2, 0, n_leds)] = CRGB(0, 0, 0);
    }

    void close_secondary_snake(int led) {
        int sec_led = n_leds - led - 1;
        leds[wrap(sec_led + n_lit_leds * 2, 0, n_leds)] = CRGB(0, 0, 0);
    }

    // Wraps a number around between s and e
    int wrap(int n, int s, int e) {
        if (n > e) {
            return s + n % (e - s);
        }
        else if (n < s) {
            return e + n % (e - s);
        }
        else {
            return n;
        }
    }

    unsigned long tick_time;

    void tick() {
        unsigned long new_time = millis();
        if ((new_time - tick_time) < tick_delay)
            delay(tick_delay - (new_time - tick_time));

        tick_time = millis();
    }
};

#endif