#include "passwd.h"

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