#ifndef passwdh
#define passwdh
#include "hint.h"
#include "eqpasswd.h"

#include <array>

class eqpasswd;
class hint;

class passwd
{
private:
    std::array<int,3> password;
    // private constructor again
    passwd(int first, int second, int third);
    ~passwd() {};
public:
    // just allows us to access elements
    int at(int) const;
    bool equals(int,int,int) const;
    static const hint* compare(const passwd &guess, const passwd &sol);

    // print password
    void printpasswd() const;
    // one friend
    friend class eqpasswd;
};
#endif