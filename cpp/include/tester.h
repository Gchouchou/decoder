#ifndef testerh
#define testerh
#include "algo.h"
// #define verbose 1

namespace printStuff
{
    void printParams(algo::algoparam &param);
    void printResults(const array<int,3*3> &results);
} // namespace printStuff

namespace tester
{
    // tests all the possible password to get a statistic
    const array<int,3*3>* testAll(const gamestate &g,const algo::algoparam &params);
} // namespace tester

#endif