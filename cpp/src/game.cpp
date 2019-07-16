#include "game.h"

using namespace game;

gamestate::gamestate() {
    turnNumber = 1;
    untestNumb = {1,2,3,4,5,6,7,8,9};
}

gamestate::gamestate(list<round*> &rounds) {
    round *aRound;
    // straight from default constructor
    turnNumber = 1;
    untestNumb = {1,2,3,4,5,6,7,8,9};
    // we now play the rounds
    while (!rounds.empty())
    {
        aRound = rounds.front();
        rounds.pop_front();
        playRound(*aRound);
    }
}

void gamestate::playRound(const round &r) {
    currPoss.updatePasswds(r.result, r.guess);
    ++turnNumber;
    updateuntest(*r.guess);
}

void gamestate::updateuntest(const passwd &guess) {
    int guesses, untest,n;
    bool ispresent;
    n = untestNumb.size();
    for (int i = 0; i < n; i++)
    {
        ispresent = false;
        untest = untestNumb.front();
        untestNumb.pop_front();
        for (int j = 0; j < 3; j++)
        {
            guesses = guess.at(j);
            if (untest == guesses) {
                ispresent = true;
            }
        }
        if (!ispresent)
        {
            untestNumb.push_back(untest);
        }
    }
}