#ifndef eqpasswdh
#define eqpasswdh

#include <list>
namespace decoder {

    class passwds;
    class passwd;
    class hint;

    class eqpasswd
    {
    private:
        // private constructor boiz
        eqpasswd(int,int,int);
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
    };
}
#endif