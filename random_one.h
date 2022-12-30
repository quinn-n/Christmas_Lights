
#ifndef RANDOM_ONE_H
#define RANDOM_ONE_H

#include <FastLED.h>


class RandomOne {
    public:
    RandomOne(CRGB* leds, int n_leds, int ms_between, int times) {
        this->leds = leds;
        this->n_leds = n_leds;
        this->ms_between = ms_between;
        this->times = times;
    }

    void random_one() {
        for (int i = 0; i < this->times; i++) {
            byte red = random(255);
            byte green = random(255);
            int led = random(n_leds);

            cur_led->r = 0;
            cur_led->g = 0;
    
            cur_led = &leds[led];
            cur_led->r = red;
            cur_led->g = green;
            FastLED.show();

            tick();
        }
    }

    private:
    CRGB* leds;
    int n_leds;
    int ms_between;
    int times;
    CRGB* cur_led;
    unsigned long tick_time;

    void tick() {
        unsigned long cur_time = millis();
        if ((cur_time - tick_time) < ms_between) {
            delay(ms_between - (cur_time - tick_time));
        }
        tick_time = millis();
    }
};

#endif
