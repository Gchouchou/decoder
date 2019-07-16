#ifndef algoh
#define algoh
#include <map>
#include <algorithm>
#include <float.h>
#include "game.h"

namespace algo {
    
    struct algoparam {
        // cscore is the constant added to every possible solution,
        double cscore;
        // sscore gives points according the how many are in eqclass,
        double sscore;
        // scale gives points proportionally to eqclass if it completely removes it,
        double scale;
        // cscale is the constant point added for clearing an eq class
        double cscale;
        // absScale is default rate at which the score increases
        double absScale;
    };

    // the algorithm calculates how many password it removes on average with bonuses:
    const passwd* selectGuess(const gamestate &g, const algoparam &params);
}
#endif