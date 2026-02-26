#ifndef ENTITE_H
#define ENTITE_H

#include <iostream>
#include <string>

using namespace std;

class Entite {
protected: 
    string name;
    int hp;
    int hpMax;
    int mp;
    int mpMax;
    int force;
    int defense;

public:
    Entite(string n, int h, int m, int f, int d);
    virtual ~Entite() {}
    virtual void recevoirDegats(int degats);

    string getName() const 
    { 
        return name; 
    }
    int getHP() const 
    {
         return hp;
         }
    int getHPMax() const
    {
         return hpMax;
    }
    int getMP() const 
    {
        return mp; 
    }
    int getMPMax() const 
    { 
        return mpMax;
    }

};
#endif