#include "passwd.h"
#include "hint.h"
#include "eqpasswd.h"

#include <algorithm>
#include <iostream>

using namespace decoder;
typedef std::array<int,PASSWORD_LENGTH> pass;

// equals method
bool passwd::equals(pass &pas) const{
    return password == pas;
}

const hint* passwd::compare(const passwd &guess, const passwd &sol) {
    int o = 0,t = 0,x = 0;
    int index = 0;
    for (auto i = guess.password.begin(); i != guess.password.end(); index++,i++)
    {
        if (std::count(sol.password.begin(),sol.password.end(),*i) != 0) {
            if (guess.password[index] == sol.password[index])
            {
                ++o;
            }
            else
            {
                ++t;
            }
        } else
        {
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
    size_t i;
    std::cout << "(";
    for (i = 0; i < PASSWORD_LENGTH - 1; i++)
    {
        std::cout << password[i] << "," << std::flush;
    }
    std::cout << password[i] << ")" << std::flush;
}