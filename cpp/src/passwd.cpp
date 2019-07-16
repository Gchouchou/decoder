#include "passwd.h"

// =========================passwd=====================

// constructor
passwd::passwd(int first, int second, int third) {
    password[0] = first;
    password[1] = second;
    password[2] = third;
}

// equals method
bool passwd::equals(int a, int b, int c) const{
    return password[0] == a && password[1] == b && password[2] == c;
}

const hint* passwd::compare(const passwd &guess, const passwd &sol) {
    int o = 0,t = 0,x = 0;
    bool b;
    for (int i = 0; i < 3; i++)
    {
        int a = guess.at( i );
        b = false;
        for (int j = 0; j < 3; j++)
        {
            if (a == sol.at( j )){
                b = true;
                if (i == j) {
                    ++o;
                }
                else {
                    ++t;
                }
                break;
            }
        }
        if (!b) {
            ++x;
        }
    }
    hint* temp = new hint(o,t,x);
    return temp;
}

int passwd::at(int index) const {
    return password[index];
}

void passwd::printpasswd() const {
    std::printf("( %d,%d,%d )", password[0],password[1],password[2]);
}

// =========================hint=====================

// constructor
hint::hint(int o, int t, int x){
    values[0] = o;
    values[1] = t;
    values[2] = x;
}

// equals method
bool hint::equals(hint &h) const {
    return values == h.values;
}

bool hint::check(const passwd &guess, const passwd &sol) const {
    // doing some memory optimization
    const hint* res = passwd::compare(guess,sol);
    bool r = this->values == res->values;
    delete(res);
    return r;
}


// =========================eqpasswd=====================

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

// =========================passwds=====================

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
    list<eqpasswd*> newallposs;
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

passwds::passwds(const list<eqpasswd*> &source) {
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