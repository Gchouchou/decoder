#ifndef converth
#define converth
#include "algo.h"

namespace converter
{
    const algo::algoparam *convert(string);
} // namespace converter

namespace calfit
{
    int cal_fitness(const gamestate *situation , const string &chromosome);
} // namespace fitness



#endif