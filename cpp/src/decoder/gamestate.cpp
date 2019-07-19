#include "gamestate.h"

using namespace decoder;

gamestate::gamestate() {
    turnNumber = 1;
    for (int i = 1; i <= 9; i++)
    {
        untestNumb.push_back(i);
    }
}

gamestate::gamestate(std::list<round*> &rounds) {
    round *aRound;
    // straight from default constructor
    turnNumber = 1;
    for (int i = 1; i <= 9; i++)
    {
        untestNumb.push_back(i);
    }
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