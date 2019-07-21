#include "passGen.h"
#include "eqpasswd.h"

#include <list>
#include <array>
#include <algorithm>

using namespace std;
using namespace decoder;
typedef array<int,PASSWORD_LENGTH> pass;

void passGen::insertPass(list<eqpasswd*> &eqpasses, pass &seq, int start, int pos) {
    // smaller or equal because we want the last number to be included
    for (int i = start; i <= CHAR_NUMB; i++)
    {
        seq[pos] = i;
        if (pos < PASSWORD_LENGTH - 1)
        {
            if (REPEAT)
            {
                // allows repeat we will always start at 1
                passGen::insertPass(eqpasses,seq,i,pos+1);
            }
            else
            {
                // we continuously increase
                passGen::insertPass(eqpasses,seq,i+1,pos+1);
            }
        }
        else if (pos == PASSWORD_LENGTH - 1)
        {
            eqpasses.push_back(new eqpasswd(seq));
        }
    }
}