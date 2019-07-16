#ifndef passwdh
#define passwdh
#include <array>
#include <list>

using namespace std;

class passwd;
class eqpasswd;

class hint
{
private:
    array<int,3> values;
public:
    // check if we what we guess and the sol gives us the right hint
    // this is allows us for easier memory allocation
    bool check(const passwd &guess, const passwd &sol) const;
    bool equals(hint &h) const;
    // this is just to put into an unordered set
    int hashed() const{return 10*values[0] + values[1];}
    hint(int o,int t,int x);
};

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
    passwds(const list<eqpasswd*> &);

    // data member
    list<eqpasswd*> passClass;
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

class eqpasswd
{
private:
    // private constructor boiz
    eqpasswd(int,int,int);
    // private method to free everything
    void empty();
    // same as update passwords
    void purgeClass(const hint *h, const passwd *p);
    // one friend
    friend passwds;

    // data member
    list<passwd*> simPasswds;
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
};

class passwd
{
private:
    array<int,3> password;
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
friend eqpasswd;
};
#endif