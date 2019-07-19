#include "population.h"
#include "decode_fitness.h"
#include "fitness_funct.h"
#include "individual.h"

int main(int argc, char const *argv[])
{
    decoder::gamestate *newGame = new decoder::gamestate();
    decode_fitness *fitnessCal = new decode_fitness(*newGame);
    genetic::individual::function = fitnessCal;
    genetic::population *people = new genetic::population();
    people->populate();
    people->writeFile();
    delete(people);
    delete(fitnessCal);
    delete(newGame);
    return 0;
}
