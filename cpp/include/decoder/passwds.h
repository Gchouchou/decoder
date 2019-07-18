#ifndef passwdsh
#define passwdsh

#include <list>

namespace decoder {
    class eqpasswd;
    class hint;
    class passwd;

    class passwds
    {
    private:
        // we are going for the first passwds is just going to be copied
        // over and over
        static int count;
        // pointer to the first copy
        static const passwds* allposs;

        // create allposs
        static void generateAllposs();

        // our custom constructor
        passwds(const std::list<eqpasswd*> &);

        // data member
        std::list<eqpasswd*> passClass;
    public:
        // getters
        static const passwds* getallposs() {return allposs;}
        // const eqpasswd* getEqClass(int i) const{return passClass[i];}
        // int getSize() const{return passClass.size();}
        // static int getCount() {return count;}
        auto cbegin() const{return passClass.cbegin();}
        auto cend() const{return passClass.cend();}

        // remove everything that doesn't correspond with the hint
        void updatePasswds(const hint *h, const passwd *p);

        // use three ints to find a pointer to the coresponding password
        static const passwd* fetch(int,int,int);

        // print all passwords
        void printpasswds() const;

        // create a set of all passwords
        passwds();
        // deep copy just the classes not the passwords
        passwds(const passwds&);
        ~passwds();
    };
}
#endif