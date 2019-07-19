#include "passwds.h"
#include "eqpasswd.h"
#include "hint.h"
#include "passwd.h"

using namespace std;
using namespace decoder;

// initialization of private static members
const passwds* passwds::allposs = nullptr;
int passwds::count = 0;

passwds::passwds() {
    if (count == 0) {
        generateAllposs();
    } 
    // taken from copy constructor
    for (auto it = allposs->passClass.begin(); it != allposs->passClass.end(); it++)
    {
        passClass.push_back(new eqpasswd(**it));
    }
    
    // increase count
    ++count;
}

void passwds::generateAllposs() {
    // at compile time so everything is good
    std::list<eqpasswd*> newallposs;
    // create all the passwords
    for (int i = 1; i < 10; i++)
    {
        for (int j = i+1; j < 10; j++)
        {
            for (int k = j+1; k < 10; k++)
            {
                newallposs.push_back(new eqpasswd(i,j,k));
            }
        }
    }
    allposs = new passwds(newallposs);
}

passwds::passwds(const std::list<eqpasswd*> &source) {
    passClass = source;
    ++count;
}

passwds::passwds(const passwds& p) {
    for (auto it = allposs->passClass.begin(); it != allposs->passClass.end(); it++)
    {
        passClass.push_back(new eqpasswd(**it));
    }
    ++count;
}

passwds::~passwds() {
    eqpasswd* point = nullptr;
    if (allposs == this && count != 1) {
        printf("Some passwords are still being used.");
        terminate();
    }
    while (!passClass.empty())
    {
        point = passClass.front();
        passClass.pop_front();
        if (allposs == this)
        {
            point->empty();
        }
        delete(point);
    }
    // set this to null at the end
    if (allposs == this)
    {
        allposs = nullptr;
    }
    // decrease count
    --count;
    // automatically delete allposs at the end
    if (count == 1) {
        delete(allposs);
    }
}

const passwd* passwds::fetch(int a,int b,int c) {
    passwd *pass = nullptr;
    for (auto it = allposs->passClass.begin(); it != allposs->passClass.end(); it++)
    {
        for (auto eqit = ( *it )->simPasswds.begin(); eqit != ( *it )->simPasswds.end(); eqit++)
        {
            pass = *eqit;
            if (pass->equals(a,b,c))
            {
                return pass;
            }
        }
    }
    return nullptr;
}

void passwds::updatePasswds(const hint *h, const passwd *p) {
    int size = passClass.size();
    eqpasswd *claz = nullptr;
    for (int i = 0; i < size; i++)
    {
        // select first, then remove it
        claz = passClass.front();
        passClass.pop_front();
        claz->purgeClass(h,p);
        if (!claz->simPasswds.empty()) {
            passClass.push_back(claz);
        } else
        {
            // we have nothing in it anymore
            delete(claz);
        }
    }
}

void passwds::printpasswds() const {
    printf("[ ");
    auto nearEnd = passClass.end();
    nearEnd--;
    for (auto it = passClass.begin(); it != passClass.end(); it++)
    {
        (*it)->printeqclass();
        if (it != nearEnd) {
            std::printf(", ");
        }
    }
    printf(" ]");
}