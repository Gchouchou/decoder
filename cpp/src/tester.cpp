#include "tester.h"
#include "algo.h"
#include "passwd.h"
#include "passwds.h"
#include "round.h"

#include <iostream>

using namespace std;

const array<int,3*3>* tester::testAll(const gamestate &g,const algo::decodeparam &params) {

    // allocated memory
    array<int,3*3> *result = new array<int,3*3>();

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
            guess = algo::selectGuess(*simulation,params);

             #if verbose>=2
            cout << "Most optimal guess is ";
            guess->printpasswd();
            cout << ".\n";
            #endif
            // loop
            while (guess != currsol && simulation->getturnNumber() < 3*3-1) {
                // create the round
                game::round r(*guess,*currsol);
                simulation->playRound(r);
                guess = algo::selectGuess(*simulation,params);

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