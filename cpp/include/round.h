#ifndef roundh
#define roundh
#include "passwd.h"
#include "hint.h"

namespace game {
    struct round
    {
        const passwd *guess;
        const hint *result;
        round(const passwd &guessed, const passwd &sol) {
            guess = &guessed;
            result = passwd::compare(guessed, sol);
        }
        // default
        round(){};
    };
}
#endif