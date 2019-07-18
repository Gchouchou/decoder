#ifndef decodefith
#define decodefith
#include "fitness_funct.h"
#include "gamestate.h"

// applied to the decoder game
class decode_fitness : AbstractFitnessCal
{
private:
    const gamestate *situation;
public:
    int cal_fitness(const std::string &chromosome) const;
    decode_fitness(const gamestate &s) {situation = new gamestate(s);}
    ~decode_fitness() {delete(situation);}
};

#endif