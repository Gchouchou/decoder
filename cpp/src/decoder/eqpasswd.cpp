#include "eqpasswd.h"
#include "passwds.h"
#include "passwd.h"
#include "hint.h"

using namespace decoder;

// constructor
eqpasswd::eqpasswd(int a, int b, int c) {
    simPasswds.push_back(new passwd(a,b,c));
    simPasswds.push_back(new passwd(a,c,b));
    simPasswds.push_back(new passwd(b,a,c));
    simPasswds.push_back(new passwd(b,c,a));
    simPasswds.push_back(new passwd(c,a,b));
    simPasswds.push_back(new passwd(c,b,a));
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