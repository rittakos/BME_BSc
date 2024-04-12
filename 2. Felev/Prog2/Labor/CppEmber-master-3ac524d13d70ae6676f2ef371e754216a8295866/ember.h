#ifndef EMBER_H_INCLUDED
#define EMBER_H_INCLUDED

#include <cstring>

class Ember
{
public:
    Ember()
    {
        nev = new char[7];
        strcpy(nev, "Z8WK8D");
        szulEv = 1999;
    }
    Ember(const char* n, int ev);
    Ember(const Ember& e);
    Ember& operator=(const Ember& e);
    virtual ~Ember();

    const char* getNev() const;
    virtual int getKor(int ev) const;
    virtual const char* foglalkozas() const;


protected:
    int szulEv;
    char* nev;
};


#endif // EMBER_H_INCLUDED
