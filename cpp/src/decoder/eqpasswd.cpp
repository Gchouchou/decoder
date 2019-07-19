#include "eqpasswd.h"
#include "passwds.h"
#include "passwd.h"
#include "hint.h"

#include <array>
#include <algorithm>

using namespace decoder;
typedef std::array<int,PASSWORD_LENGTH> pass;

// constructor
eqpasswd::eqpasswd(pass &sequence) {
    // use standard library to create all permutations
    do
    {
        simPasswds.push_back(new passwd(sequence));
    } while (std::next_permutation(sequence.begin(),sequence.end()));
}


// basically the real destructor
void eqpasswd::empty() {
    passwd *p = nullptr;
    while (!simPasswds.empty())
    {
        p = simPasswds.front();
        simPasswds.pop_front();
        delete(p);
    }
}

void eqpasswd::purgeClass(const hint *h, const passwd *p){
    int size = simPasswds.size();
    passwd *sol = nullptr;
    for (int i = 0; i < size; i++)
    {
        sol = simPasswds.front();
        simPasswds.pop_front();
        if (h->check(*p, *sol)) {
            simPasswds.push_back(sol);
        }
    }
}

void eqpasswd::printeqclass() const {
    std::printf("[");
    auto nearEnd = simPasswds.end();
    nearEnd--;
    for (auto i = simPasswds.begin(); i != simPasswds.end(); i++)
    {
        (*i)->printpasswd();
        if (i != nearEnd) {
            std::printf(", ");
        }
    }
    std::printf("]");
}