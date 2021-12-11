/*
 * breathe.h
 * Breathing mode for christmas lights.
 * Written by Quinn Neufeld
 * Dec. 10 2021
 */

#ifndef BREATHE_H
#define BREATHE_H

#include <FastLED.h>

#define BREATHE_RED 1
#define BREATHE_GREEN 2

class Breathe {
    public:
    Breathe(CRGB* leds, int n_leds, unsigned long breath_time, int times) {
        this->leds = leds;
        this->n_leds = n_leds;
        this->breath_time = breath_time;
        this->times = times;
    }

    void breathe() {
        for (int b = 0; b < times; b++) {
            unsigned long s_time = millis();
            unsigned long e_time = millis() + breath_time;
            int colour = random(1, 3);
            while (millis() < e_time) {
                int val = sine(millis() - s_time);
                switch (colour) {
                    case BREATHE_RED:
                        for (int i = 0 ; i < n_leds; i++) {
                            leds[i].r = val;
                        }
                        break;
                    case BREATHE_GREEN:
                        for (int i = 0; i < n_leds; i++) {
                            leds[i].g = val;
                        }
                        break;
                };
                FastLED.show();
            }
        }
    }

    private:
    CRGB* leds;
    int n_leds;
    unsigned long breath_time;
    int times;

    // Returns result of modified sine function
    int sine(unsigned long x) {
        return floor(((sin(((2 * x - breath_time / 2.) * PI) / breath_time) + 1.) / 2.) * 255.);
    }

    // Clears colour buffer of each LED
    void clear_leds() {
        for (int i = 0; i < n_leds; i++) {
            leds[i] = CRGB(0, 0, 0);
        }
    }
};

#endif
