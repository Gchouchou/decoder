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