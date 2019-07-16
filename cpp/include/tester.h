#ifndef testerh
#define testerh
#include "decode_param.h"
#include "gamestate.h"

#include <array>
// #define verbose 1

namespace tester
{
    // tests all the possible password to get a statistic
    const std::array<int,3*3>* testAll(const gamestate &g,const algo::decodeparam &params);
} // namespace tester

#endif