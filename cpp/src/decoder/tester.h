#ifndef testerh
#define testerh
#include "decode_param.h"
#include "gameSettings.h"

#include <array>
#define verbose 2

namespace decoder
{
    class gamestate;
    // tests all the possible password to get a statistic
    const std::array<int,RESULT_LENGTH>* testAll(const gamestate &g,const decoder::decodeparam &params);
} // namespace tester

#endif