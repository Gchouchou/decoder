#ifndef eqpasswdh
#define eqpasswdh
#include "gameSettings.h"
#include "passGen.h"

#include <list>
#include <array>
namespace decoder {

    class passwds;
    class passwd;
    class hint;

    class eqpasswd
    {
    private:
        // generalized constructor
        eqpasswd(std::array<int,PASSWORD_LENGTH>&);
        // private method to free everything
        void empty();
        // same as update passwords
        void purgeClass(const hint *h, const passwd *p);

        // data member
        std::list<passwd*> simPasswds;
    public:
        // getter
        // const passwd* getPasswd(int i) const{return simPasswds[i];}
        int getSize() const{return simPasswds.size();}
        // let's hope this does something
        auto cbegin() const{return simPasswds.cbegin();}
        auto cend() const{return simPasswds.cend();}

        // print all passwords in eqclass
        void printeqclass() const;
        // ~eqpasswd();

        // one friend
        friend class passwds;
        friend void passGen::insertPass(std::list<eqpasswd*> &eqpasses,\
        std::array<int,PASSWORD_LENGTH> &seq, int start, int pos);
    };
}
#endif