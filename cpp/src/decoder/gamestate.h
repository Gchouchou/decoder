#ifndef gamestateh
#define gamestateh
#include "round.h"
#include "passwds.h"

#include <list>

namespace decoder {
    class gamestate
    {
    private:
        void updateuntest(const passwd &);

        // data members
        passwds currPoss;
        int turnNumber;
        std::list<int> untestNumb;
    public:
        // plays the round
        void playRound(const decoder::round&);

        // getters
        const passwds* getcurrPoss() const{return &currPoss;}
        const int getturnNumber() const{return turnNumber;}
        const std::list<int>* getuntestNumb() const{return &untestNumb;}

        // creates a new game with every possibility
        gamestate();
        // plays all the rounds to reach desired game state
        gamestate(std::list<decoder::round*> &rounds);
    };
}
#endif