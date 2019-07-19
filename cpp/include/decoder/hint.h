#ifndef hinth
#define hinth

#include <array>

namespace decoder {

    class passwd;

    class hint
    {
    private:
        std::array<int,3> values;
    public:
        // check if we what we guess and the sol gives us the right hint
        // this is allows us for easier memory allocation
        bool check(const passwd &guess, const passwd &sol) const;
        bool equals(hint &h) const;
        // this is just to put into an unordered set
        int hashed() const{return 10*values[0] + values[1];}
        hint(int o,int t,int x);
    };
}
#endif