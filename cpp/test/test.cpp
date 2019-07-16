#include "tester.h"

using namespace algo;

int main() {
    gamestate *game = new gamestate();
    algoparam a;
    a.absScale = 1;
    a.cscale = 0.5;
    a.sscore = 0.2;
    a.cscore = 5.5;
    a.scale = 0.2;
    tester::testAll(*game, a);




    delete(game);
}