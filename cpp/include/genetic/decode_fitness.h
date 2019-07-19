#ifndef decodefith
#define decodefith
#include "fitness_funct.h"
#include "gamestate.h"

// applied to the decoder game
class decode_fitness : public genetic::abstractFitnessCal
{
private:
    const decoder::gamestate situation;
public:
    int cal_fitness(const std::string &chromosome) const;
    decode_fitness(const decoder::gamestate &s) : situation(s){}
};

#endif