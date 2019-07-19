#include "tester.h"
#include "algo.h"
#include "passwd.h"
#include "eqpasswd.h"
#include "passwds.h"
#include "round.h"
#include "gamestate.h"
#include "gameSettings.h"
#include "printObj.h"

#include <iostream>

using namespace std;
using namespace decoder;

const array<int,RESULT_LENGTH>* decoder::testAll(const gamestate &g,const decoder::decodeparam &params) {
    array<int,3> a {1,4,3};

    // allocated memory
    array<int,RESULT_LENGTH> *result = new array<int,RESULT_LENGTH>();

    // constants
    const passwds *allposs = passwds::getallposs();

    // pointers
    gamestate *simulation;
    const passwd *currsol;
    const passwd *guess = nullptr;
    for (auto it = allposs->cbegin(); it != allposs->cend(); it++) {
        for (auto eit = (*it)->cbegin(); eit != (*it)->cend(); eit++) {
            // initialize variables
            currsol = *eit;
            simulation = new gamestate(g);

             #if verbose>=2
            // some good debug text
            cout << "The current solution is ";
            currsol->printpasswd();
            cout << ".\n" << flush;
            #endif

            // keep guessing and and update
            guess = selectGuess(*simulation,params);

             #if verbose>=2
            cout << "Most optimal guess is ";
            guess->printpasswd();
            cout << ".\n";
            #endif
            // loop
            while (guess != currsol && simulation->getturnNumber() < RESULT_LENGTH-1) {
                if (currsol == passwds::fetch(a))
                    cout << "abcwtf";
                // create the round
                round r(*guess,*currsol);
                simulation->playRound(r);
                guess = selectGuess(*simulation,params);

                 #if verbose>=2
                cout << "Most optimal guess is ";
                guess->printpasswd();
                cout << ".\n";
                #endif
            }
            // briefly compile results
             #if verbose>=2
            cout << "Solution found on turn " << simulation->getturnNumber() << ".\n" << flush;
            #endif
            ++result->at(simulation->getturnNumber());
            // free memory
            delete(simulation);
        }
    }

    #if verbose>=1
    cout << "With parameters ";
    printParams(params);
    cout << " obtained ";
    printResults(*result);
    cout << ".\n" << flush;
    #endif

    return result;
}