#include "tester.h"

#include <iostream>
#include <iomanip>

using namespace printStuff;
using namespace algo;
using namespace game;

const array<int,3*3>* tester::testAll(const gamestate &g,const algoparam &params) {

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
            guess = selectGuess(*simulation,params);

             #if verbose>=2
            cout << "Most optimal guess is ";
            guess->printpasswd();
            cout << ".\n";
            #endif
            // loop
            while (guess != currsol && simulation->getturnNumber() < 3*3-1) {
                // create the round
                struct round r(*guess,*currsol);
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

void printStuff::printParams(algoparam &params) {
    cout << "[" << setprecision(2) << params.cscore << ", ";
    cout << setprecision(2) << params.sscore  << ", ";
    cout << setprecision(2) << params.cscale  << ", ";
    cout << setprecision(2) << params.scale << ", ";
    cout << setprecision(2) << params.absScale;
    cout << "]";
}

void printStuff::printResults(const array<int,3*3> &results) {
    int index = 0;
    cout << "[";
    for (auto it = results.begin(); it != results.end(); it++, index++) {
        cout << *it;
        if (index != 8) {
            cout << ", ";
        }
    }
    cout << "]";
}