#include "hint.h"

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