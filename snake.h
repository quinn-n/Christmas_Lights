
/*
 * snake.h
 * Runs a 'snake' down the length of the wire
 * Written by Quinn Neufeld
 * Dec. 10 2021
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <FastLED.h>

#define SNAKE_N_COLOURS floor(sizeof(SNAKE_COLOURS) / sizeof(CRGB))
static const CRGB SNAKE_COLOURS[] = {
    CRGB(255, 0, 0),
    CRGB(0, 255, 0)
};

class Snake {
    public:
    Snake(CRGB* leds, int n_leds, int n_lit_leds, int tick_delay, int times) {
        this->leds = leds;
        this->n_leds = n_leds;
        this->n_lit_leds = n_lit_leds;
        this->tick_delay = tick_delay;
        this->times = times;
    }
    void snake() {
        for (int i = 0; i < n_lit_leds; i++) {
            leds[i] = pick_colour();
            FastLED.show();
            tick();
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
        leds[wrap(cur_led, 0, n_leds)] = CRGB(0, 0, 0);
        //Set LED at the end of the chain
        leds[wrap(cur_led + n_lit_leds, 0, n_leds)] = pick_colour();
    }

    // Clears last LED. Used when the snake is ending
    void update_last_leds(int led) {
        leds[wrap(led, 0, n_leds)] = CRGB(0, 0, 0);

        // Only turn on the next led if it hasn't wrapped back around
        int set_led = wrap(led + n_lit_leds, 0, n_leds);
        if (set_led > led) {
            leds[set_led] = pick_colour();
        }
    }

    // Wraps a number around between s and e
    int wrap(int n, int s, int e) {
        return n % (e - s);
    }
};

#endif
