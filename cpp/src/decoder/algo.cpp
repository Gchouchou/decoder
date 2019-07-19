#include "algo.h"
#include "gamestate.h"
#include "eqpasswd.h"
#include "passwds.h"
#include "hint.h"
#include "passwd.h"

#include <map>
#include <algorithm>

using namespace std;
using namespace decoder;

struct untestn
{ 
    list<int> *needed;
    list<int> *uneeded;
    untestn(const list<int> &untested);
    ~untestn(){delete(needed); delete(uneeded); }
 };


namespace decoder::algoHelpers
{
    // gives a list with all of the possible guesses
    list<const passwd*>* getPossGuess(const list<int> &untestnumb);
    namespace searchOpt
    {
        // purging unwanted eqclasses
        bool isUnwanted(const eqpasswd &claz, list<int> &unwanted);
        // cleaning some passwords
        bool wrongOrder(const passwd &pass, list<int> &untested);
        // helper of the helper
        bool order(int first,int second, list<int> &untested);
    } // namespace searchOpt
    double evaluateHint(const hint &h, const passwd &guess, const passwds &currpos, double scale, double cscale, double absScale);
} // namespace algoHelpers

const passwd* decoder::selectGuess(const gamestate &g, const decodeparam &params) {
    double bestscore = -__DBL_MAX__ +2,score = 0;
    double subscore;
    int eqrsolsize;
    const hint *evaluation;
    const passwd *guess,*rsol,*best;
    // map of the score of each hint
    map<int, double> hintscores;
    list<const passwd*> *allguess = algoHelpers::getPossGuess(*g.getuntestNumb());
    const passwds *allsol = g.getcurrPoss();
    // allsol is not going to change size

    for (auto a = allguess->begin(); a != allguess->end(); a++)
    {
        guess = *a;
        hintscores.clear();
        // score of the guess
        score = 0;
        // iterate through all the possible solutions
        for (auto b = allsol->cbegin(); b != allsol->cend(); b++)
        {
            eqrsolsize = (*b)->getSize();
            for (auto c = (*b)->cbegin(); c != (*b)->cend(); c++)
            {
                // assume that the real sol is rsol
                rsol = *c;
                // give bonuses to guess if it is itself a sol
                if (guess == rsol) {
                    score += params.cscore + params.sscore*eqrsolsize;
                }
                evaluation = passwd::compare(*guess, *rsol);
                if (hintscores.count(evaluation->hashed()) == 1) {
                    score += (hintscores.find(evaluation->hashed()))->second;
                } else {
                    subscore = algoHelpers::evaluateHint(*evaluation, *guess,*allsol, params.scale \
                    , params.cscale, params.absScale);
                    hintscores.emplace(evaluation->hashed(), subscore);
                    score += subscore;
                }
                delete(evaluation);
            }
        }
        if (score > bestscore)
        {
            bestscore = score;
            best = guess;
        }
    }

    // free memory
    delete(allguess);
    return best;
}

list<const passwd*>* algoHelpers::getPossGuess(const list<int> &untestnumb) {
    const passwd *pass;

    // get the unwanted numbers
    untestn* numb = new untestn(untestnumb);

    // create the list of good guesses, and obtain all possible passwords
    list<const passwd*> *goodGuess = new list<const passwd*>();
    const passwds *alltries = passwds::getallposs();
    for (auto it = alltries->cbegin(); it != alltries->cend(); it++)
    {
        if (searchOpt::isUnwanted(**it, *(numb->uneeded) )){
            continue;
        }
        for (auto eqit = (*it)->cbegin(); eqit != (*it)->cend(); eqit++)
        {
            pass = *eqit;
            if (!searchOpt::wrongOrder(*pass, *(numb->needed))) {
                goodGuess->push_back(pass);
            }
        }
    }
    // free memory
    delete(numb);

    return goodGuess;
}


untestn::untestn(const list<int> &untested) {
    int index = 0;
    list<int> *needed = new list<int>();
    list<int> *uneeded= new list<int>();
    this->needed = needed;
    this->uneeded = uneeded;
    for (auto it = untested.cbegin(); it != untested.cend(); it++,index++)
    {
        if (index < 3) {
            needed->push_back(*it);
        } else {
            uneeded->push_back(*it);
        }
    }
}


bool algoHelpers::searchOpt::isUnwanted(const eqpasswd &claz, list<int> &unwanted) {
    int i;
    // get a password
    const passwd *pass = *claz.cbegin();
    for (i = 0; i < 3; i++)
    {
        if (find(unwanted.begin(),unwanted.end(), pass->at(i)) != unwanted.end()) {
            // contains an unwanted number
            return true;
        }
    }
    return false;
}

// the algorithm is not generalized
bool algoHelpers::searchOpt::wrongOrder(const passwd &pass, list<int> &untested) {
    // if the untested numbers are untested, they must be in increasing order
    return order(pass.at(0),pass.at(1),untested) || order(pass.at(0),pass.at(2),untested) || \
    order(pass.at(1),pass.at(2),untested);
}

bool algoHelpers::searchOpt::order(int first,int second, list<int> &untested) {
    return (find(untested.begin(), untested.end(), first) != untested.end()) && \
    (find(untested.begin(), untested.end(), second) != untested.end()) && first > second;
}


double algoHelpers::evaluateHint(const hint &h, const passwd &guess, const passwds &allsol, \
double scale, double cscale, double absScale) {
    double subscore = 0;
    bool removedAll;
    int eqtsolsize;
    for (auto b = allsol.cbegin(); b != allsol.cend(); b++)
    {
        eqtsolsize = (*b)->getSize();
        removedAll = true;
        for (auto c = (*b)->cbegin(); c != (*b)->cend(); c++) 
        {
            if (!h.check(guess,**c))
            {
                subscore += absScale;
            } else
            {
                // there is one that hasn't been removed
                removedAll = false;
            }
        }
        if (removedAll) {
            subscore += cscale + scale*eqtsolsize;
        }
    }
    return subscore;
}