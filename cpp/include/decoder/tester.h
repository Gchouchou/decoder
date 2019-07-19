#ifndef testerh
#define testerh
#include "decode_param.h"

#include <array>
// #define verbose 1

namespace decoder
{
    class gamestate;
    // tests all the possible password to get a statistic
    const std::array<int,3*3>* testAll(const gamestate &g,const decoder::decodeparam &params);
} // namespace tester

#endif