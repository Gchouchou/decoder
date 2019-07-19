#ifndef algoh
#define algoh
#include "decode_param.h"

namespace decoder {

    class gamestate;
    class passwd;

    // the algorithm calculates how many password it removes on average with bonuses:
    const passwd* selectGuess(const gamestate &g, const decodeparam &params);
}
#endif