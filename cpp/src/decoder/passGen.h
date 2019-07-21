#ifndef passGenh
#define passGenh
#include "gameSettings.h"

#include <list>
#include <array>
namespace decoder {
    class eqpasswd;
    namespace passGen{
        // inserts passwords using recursion and loops
        // start refers to the starting index of the loop
        // pos refers to which position we're setting
        void insertPass(std::list<eqpasswd*> &eqpasses, std::array<int,PASSWORD_LENGTH> &seq, int start, int pos);
    }
}
#endif