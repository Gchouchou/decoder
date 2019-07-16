#ifndef gamestateh
#define gamestateh
#include "passwd.h"

namespace game {
    struct round
    {
        const passwd *guess;
        const hint *result;
        round(const passwd &guessed, const passwd &sol) {
            guess = &guessed;
            result = passwd::compare(guessed, sol);
        }
        // default
        round(){};
    };
}
class gamestate
{
private:
    void updateuntest(const passwd &);

    // data members
    passwds currPoss;
    int turnNumber;
    list<int> untestNumb;
public:
    // plays the round
    void playRound(const game::round&);

    // getters
    const passwds* getcurrPoss() const{return &currPoss;}
    const int getturnNumber() const{return turnNumber;}
    const list<int>* getuntestNumb() const{return &untestNumb;}

    // creates a new game with every possibility
    gamestate();
    // plays all the rounds to reach desired game state
    gamestate(list<game::round*> &rounds);
};

#endif