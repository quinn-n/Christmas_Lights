
#ifndef OVERLAPPED_SNAKE_H
#define OVERLAPPED_SNAKE_H

#include <FastLED.h>

#include "snake.h" // Directions

class OverlappedSnake {
    public:
    OverlappedSnake(CRGB* leds, int n_leds, int start_direction, int tick_delay, int times) {
        this->leds = leds;
        this->n_leds = n_leds;
        this->start_direction = start_direction;
        this->tick_delay = tick_delay,
        this->times = times;
    }

    void overlapped_snake() {
        int colour_id = random(SNAKE_N_COLOURS);
        const CRGB* start_colour = &SNAKE_COLOURS[colour_id];
        int end_colour_id;
        if (colour_id == 0)
            end_colour_id = 1;
        else if (colour_id == 1)
            end_colour_id = 0;
        const CRGB* end_colour = &SNAKE_COLOURS[end_colour_id];
        for (int n = 0; n < times; n++) {
            if (start_direction == SNAKE_FOR) {
                // First snake
                for (int i = 0; i < n_leds; i += 2) {
                    leds[i] = *start_colour;
                    FastLED.show();
                    tick();
                }
                // Second snake
                for (int i = n_leds - 1; i >= 0; i -= 2) {
                    leds[i] = *end_colour;
                    FastLED.show();
                    tick();
                }
                // Clear first snake
                for (int i = 0; i < n_leds; i += 2) {
                    leds[i] = CRGB(0, 0, 0);
                    FastLED.show();
                    tick();
                }
                // Second snake
                for (int i = n_leds - 1; i >= 0; i -= 2) {
                    leds[i] = CRGB(0, 0, 0);
                    FastLED.show();
                    tick();
                }
            }
            else {
                // First snake
                for (int i = n_leds - 1; i >= 0; i -= 2) {
                    leds[i] = *start_colour;
                    FastLED.show();
                    tick();
                }
                // Second snake
                for (int i = 0; i < n_leds; i += 2) {
                    leds[i] = *end_colour;
                    FastLED.show();
                    tick();
                }
                // Clear first snake
                for (int i = n_leds - 1; i >= 0; i -= 2) {
                    leds[i] = CRGB(0, 0, 0);
                    FastLED.show();
                    tick();
                }
                // Clear second snake
                for (int i = 0; i < n_leds; i += 2) {
                    leds[i] = CRGB(0, 0, 0);
                    FastLED.show();
                    tick();
                }
            }
        }
    }

    private:
    CRGB* leds;
    int n_leds;
    int start_direction;
    int tick_delay;
    int times;

    unsigned long tick_time;

    void tick() {
        unsigned long new_time = millis();
        if ((new_time - tick_time) < tick_delay)
            delay(tick_delay - (new_time - tick_time));

        tick_time = millis();
    }
};

#endif
