#ifndef passwdh
#define passwdh
#include "gameSettings.h"

#include <array>

namespace decoder {
    class eqpasswd;
    class hint;

    class passwd
    {
    private:
        std::array<int,PASSWORD_LENGTH> password;
        // generalized constructor
        passwd(std::array<int,PASSWORD_LENGTH> &a) : password(a){}
        ~passwd() {};
    public:
        // just allows us to access elements
        int at(int) const;
        bool equals(std::array<int,PASSWORD_LENGTH>&) const;
        static const hint* compare(const passwd &guess, const passwd &sol);

        // print password
        void printpasswd() const;
        // one friend
        friend class eqpasswd;
    };
}
#endif