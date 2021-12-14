
#ifndef OVERLAPPED_BREATHE_H
#define OVERLAPPED_BREATHE_H

#include <FastLED.h>

#include "breathe.h"

class OverlappedBreathe {
    public:
    OverlappedBreathe(CRGB* leds, int n_leds, unsigned long breath_time, int times) {
        this->leds = leds;
        this->n_leds = n_leds;
        this->breath_time = breath_time;
        this->times = times;
    }

    void overlapped_breathe() {
        int primary_colour = random(1, 3);
        start_leds(primary_colour);
        for (int b = 0; b < times; b++) {
            unsigned long s_time = millis();
            unsigned long e_time = s_time + breath_time;
            while (millis() < e_time) {
                int val1 = sine(millis() - s_time);
                int val2 = sine(millis() - s_time + breath_time / 2);
                for (int i = 0; i < n_leds; i += 2) {
                    if (primary_colour == BREATHE_RED) {
                        leds[i].r = val1;
                        leds[i + 1].g = val2;
                    }
                    else if (primary_colour == BREATHE_GREEN) {
                        leds[i].g = val1;
                        leds[i + 1].r = val2;
                    }
                }
                FastLED.show();
            }
        }
        Serial.println("Stopping leds");
        stop_leds(primary_colour);
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

    // Start first set of LEDs
    void start_leds(int primary_colour) {
        unsigned long s_time = millis();
        unsigned long e_time = millis() + breath_time / 2;
        while (millis() < e_time) {
            int val = sine(millis() - s_time);
            for (int i = 1; i < n_leds; i += 2) {
                if (primary_colour == BREATHE_RED) {
                    leds[i].g = val;
                }
                else if (primary_colour == BREATHE_GREEN) {
                    leds[i].r = val;
                }
            }
            FastLED.show();
        }
    }
    
    // Stop last set of LEDs
    void stop_leds(int primary_colour) {
        unsigned long s_time = millis();
        unsigned long e_time = millis() + breath_time / 2;
        while (millis() < e_time) {
            int val = sine(millis() - s_time + breath_time / 2);
            for (int i = 1; i < n_leds; i += 2) {
                if (primary_colour == BREATHE_RED) {
                    leds[i].g = val;
                }
                else if (primary_colour == BREATHE_GREEN) {
                    leds[i].r = val;
                }
            }
            FastLED.show();
        }
    }
};

#endif
