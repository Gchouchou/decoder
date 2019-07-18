#ifndef roundh
#define roundh
#include "passwd.h"
#include "hint.h"

namespace decoder {
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