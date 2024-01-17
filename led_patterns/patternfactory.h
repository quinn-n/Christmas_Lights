
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
        // Build new pattern
        LEDPattern* p = NULL;
        if (pattern == Pattern::Snake) {
            p = new Snake(leds, n_leds, random(1, 100), random(1, 3), random(15, 50), random(4, 10));
        }
        else if (pattern == Pattern::OverlappedSnake) {
            p = new OverlappedSnake(leds, n_leds, random(1, 3), random(15, 50), random(4, 10));
        }
        else if (pattern == Pattern::DoubleSnake) {
            p = new DoubleSnake(leds, n_leds, random(10, 50), random(15, 50), random(4, 10));
        }
        else if (pattern == Pattern::Breathe) {
            p = new Breathe(leds, n_leds, random(5000, 20000), random(3, 8));
        }
        else if (pattern == Pattern::OverlappedBreathe) {
            p = new OverlappedBreathe(leds, n_leds, random(5000, 20000), random(3, 8));
        }
        else if (pattern == Pattern::RandomOne) {
            p = new RandomOne(leds, n_leds, random(100, 200), random(300, 450));
        }
        else if (pattern == Pattern::RandomAll) {
            p = new RandomAll(leds, n_leds, random(150, 500), random(4, 10));
        }

        return p;
    }
    private:
    CRGB* leds = NULL;
    int n_leds = -1;
};

#endif
