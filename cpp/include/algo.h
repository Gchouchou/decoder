#ifndef algoh
#define algoh
#include "gamestate.h"
#include "decode_param.h"

namespace algo {

    // the algorithm calculates how many password it removes on average with bonuses:
    const passwd* selectGuess(const gamestate &g, const decodeparam &params);
}
#endif