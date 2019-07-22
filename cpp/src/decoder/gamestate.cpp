#include "gamestate.h"
#include "gameSettings.h"

#include <algorithm>

using namespace decoder;

gamestate::gamestate() {
    turnNumber = 1;
    for (int i = 1; i <= CHAR_NUMB; i++)
    {
        untestNumb.push_back(i);
    }
}

gamestate::gamestate(std::list<round*> &rounds) {
    round *aRound;
    // straight from default constructor
    turnNumber = 1;
    for (int i = 1; i <= CHAR_NUMB; i++)
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
    int untest,n;
    n = untestNumb.size();
    for (int i = 0; i < n; ++i)
    {
        untest = untestNumb.front();
        untestNumb.pop_front();
        // if not present
        if (std::count(guess.cbegin(),guess.cend(),untest) == 0)
        {
            untestNumb.push_back(untest);
        }
    }
}