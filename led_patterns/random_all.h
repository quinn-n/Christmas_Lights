#ifndef RANDOM_ALL_H
#define RANDOM_ALL_H

#include <FastLED.h>

#include <ArduinoSTL.h>

#include "ledpattern.h"

class RandomAll : public LEDPattern {
    public:
    RandomAll(CRGB* leds, int n_leds, int ms_between, int times) {
        this->leds = leds;
        this->n_leds = n_leds;
        this->ms_between = ms_between;
        this->times = times;
    }

    void run() {
        std::vector<bool> cur_state_leds;

        for (int i = 0; i < times * 2; i++) {
            cur_state_leds.resize(n_leds);
            for (int i = 0; i < n_leds; i++) {
                cur_state_leds[i] = true;
            }

            // Turn on / off leds one by one
            for (int leds_to_change = n_leds; leds_to_change > 0; leds_to_change--) {
                int led_pos = random(leds_to_change);
                int led = to_change_pos(cur_state_leds, led_pos);
                if (i % 2 == 0) {
                    light_led(&leds[led]);
                } else {
                    unlight_led(&leds[led]);
                }
                cur_state_leds[led] = false;
                tick();
            }
        }
    }

    private:
    CRGB* leds;
    int n_leds;
    int ms_between;
    int times;

    unsigned long tick_ms;

    void light_led(CRGB* led) {
        led->r = random(255);
        led->g = random(255);
        FastLED.show();
    }

    void unlight_led(CRGB* led) {
        led->r = 0;
        led->g = 0;
        FastLED.show();
    }

    size_t to_change_pos(std::vector<bool> &cur_state_leds, int led_pos) {
        for (size_t i = 0; i < cur_state_leds.size(); i++) {
            if (cur_state_leds[i]) {
                led_pos--;
                if (led_pos < 0) {
                    return i;
                }
            }
        }
    }

    void tick() {
        unsigned long cur_ms = millis();
        if ((cur_ms - tick_ms) < ms_between) {
            delay((ms_between - (cur_ms - tick_ms)));
        }
    }
};

#endif
