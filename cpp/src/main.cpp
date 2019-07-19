// #include "population.h"
// #include "gamestate.h"
// #include "decode_fitness.h"
// #include "fitness_funct.h"
// #include "individual.h"

// int main(int argc, char const *argv[])
// {
//     decoder::gamestate *newGame = new decoder::gamestate();
//     decoder::decode_fitness *fitnessCal = new decoder::decode_fitness(*newGame);
//     genetic::individual::function = fitnessCal;
//     genetic::population *people = new genetic::population();

//     people->populate();
//     people->writeFile();

//     delete(people);
//     delete(fitnessCal);
//     delete(newGame);
//     return 0;
// }

#include "gamestate.h"
#include "tester.h"
#include "decode_param.h"
#include "printObj.h"

using namespace decoder;

int main() {
    gamestate *game = new gamestate();
    decodeparam a;
    a.absScale = 1;
    a.cscale = 0.5;
    a.sscore = 0.2;
    a.cscore = 5.5;
    a.scale = 0.2;
    printResults(*testAll(*game, a));




    delete(game);
}