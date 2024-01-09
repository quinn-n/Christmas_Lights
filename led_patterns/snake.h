
/*
 * snake.h
 * Runs a 'snake' down the length of the wire
 * Written by Quinn Neufeld
 * Dec. 10 2021
 * Dec. 12 2021 - Added reverse snake
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <FastLED.h>

#include "ledpattern.h"

#define SNAKE_FOR 1
#define SNAKE_REV 2

#define SNAKE_N_COLOURS floor(sizeof(SNAKE_COLOURS) / sizeof(CRGB))
static const CRGB SNAKE_COLOURS[] = {
    CRGB(255, 0, 0),
    CRGB(0, 255, 0)
};

class Snake : public LEDPattern {
    public:
    Snake(CRGB* leds, int n_leds, int n_lit_leds, int direction, int tick_delay, int times) {
        this->leds = leds;
        this->n_leds = n_leds;
        this->n_lit_leds = n_lit_leds;
        this->direction = direction;
        this->tick_delay = tick_delay;
        this->times = times;
    }
    void run() {
        if (direction == SNAKE_FOR) {
            for (int i = 0; i < n_lit_leds; i++) {
                leds[i] = pick_colour();
                FastLED.show();
                tick();
            }
        }
        else if (direction == SNAKE_REV) {
            for (int i = n_leds - 1; i > n_leds - n_lit_leds - 1; i--) {
                leds[i] = pick_colour();
                FastLED.show();
                tick();
            }
        }

        for (int i = 0; i < times; i++) {
            for (int cur_led = 0; cur_led < n_leds; cur_led++) {
                if (i < times - 1) {
                    update_leds(cur_led);
                }
                else {
                    update_last_leds(cur_led);
                }
                FastLED.show();

                tick();
            }
        }
    }

    private:
    CRGB* leds;
    int n_leds;
    int n_lit_leds;
    int direction;
    int tick_delay;
    int times;

    unsigned long tick_time;

    void tick() {
        unsigned long new_time = millis();
        if ((new_time - tick_time) < tick_delay)
            delay(tick_delay - (new_time - tick_time));

        tick_time = millis();
    }

    // Returns a random colour from SNAKE_COLOURS
    CRGB pick_colour() {
        return SNAKE_COLOURS[random(SNAKE_N_COLOURS)];
    }
    
    // Updates the chain of lit LEDs
    void update_leds(int cur_led) {
        //Clear last LED
        if (direction == SNAKE_FOR) {
            leds[wrap(cur_led, 0, n_leds)] = CRGB(0, 0, 0);
        }
        else if (direction == SNAKE_REV) {
            leds[wrap(n_leds - cur_led - 1, 0, n_leds)] = CRGB(0, 0, 0);
        }
        //Set LED at the end of the chain
        if (direction == SNAKE_FOR) {
            leds[wrap(cur_led + n_lit_leds, 0, n_leds)] = pick_colour();
        }
        else if (direction == SNAKE_REV) {
            leds[wrap(n_leds - cur_led - n_lit_leds - 1, 0, n_leds)] = pick_colour();
        }
    }

    // Clears last LED. Used when the snake is ending
    void update_last_leds(int cur_led) {
        if (direction == SNAKE_FOR) {
            leds[wrap(cur_led, 0, n_leds)] = CRGB(0, 0, 0);
        }
        else if (direction == SNAKE_REV) {
            leds[wrap(n_leds - cur_led - 1, 0, n_leds)] = CRGB(0, 0, 0);
        }

        // Only turn on the next led if it hasn't wrapped back around
        if (direction == SNAKE_FOR) {
            int set_led = wrap(cur_led + n_lit_leds, 0, n_leds);
            if (set_led > cur_led) {
                leds[set_led] = pick_colour();
            }
        }
        else if (direction == SNAKE_REV) {
            int set_led = wrap(n_leds - cur_led - n_lit_leds - 1, 0, n_leds);
            if (set_led < n_leds - cur_led - 1) {
                leds[set_led] = pick_colour();
            }
        }
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
};

#endif
