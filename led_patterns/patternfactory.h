
#ifndef PATTERNFACTORY_H
#define PATTERNFACTORY_H

#include "snake.h"
#include "overlapped_snake.h"
#include "double_snake.h"
#include "breathe.h"
#include "overlapped_breathe.h"
#include "random_one.h"
#include "random_all.h"

enum class Pattern {
    Snake = 1,
    OverlappedSnake = 2,
    DoubleSnake = 3,
    Breathe = 4,
    OverlappedBreathe = 5,
    RandomOne = 6,
    RandomAll = 7
};

class LEDPatternFactory {
    public:
    LEDPatternFactory(CRGB* leds, int n_leds) {
        this->leds = leds;
        this->n_leds = n_leds;
    }

    LEDPattern* build_pattern(Pattern pattern) {
        // Cleanup old led pattern
        if (current_pattern != NULL) {
            delete current_pattern;
            current_pattern = NULL;
        }

        // Build new pattern
        if (pattern == Pattern::Snake) {
            current_pattern = new Snake(leds, n_leds, random(1, 100), random(1, 3), random(15, 50), random(4, 10));
        }
        else if (pattern == Pattern::OverlappedSnake) {
            current_pattern = new OverlappedSnake(leds, n_leds, random(1, 3), random(15, 50), random(4, 10));
        }
        else if (pattern == Pattern::DoubleSnake) {
            current_pattern = new DoubleSnake(leds, n_leds, random(10, 50), random(15, 50), random(4, 10));
        }
        else if (pattern == Pattern::Breathe) {
            current_pattern = new Breathe(leds, n_leds, random(5000, 20000), random(3, 8));
        }
        else if (pattern == Pattern::OverlappedBreathe) {
            current_pattern = new OverlappedBreathe(leds, n_leds, random(5000, 20000), random(3, 8));
        }
        else if (pattern == Pattern::RandomOne) {
            current_pattern = new RandomOne(leds, n_leds, random(100, 200), random(300, 450));
        }
        else if (pattern == Pattern::RandomAll) {
            current_pattern = new RandomAll(leds, n_leds, random(150, 500), random(4, 10));
        }

        return current_pattern;
    }
    private:
    LEDPattern* current_pattern = NULL;
    CRGB* leds = NULL;
    int n_leds = -1;
};

#endif