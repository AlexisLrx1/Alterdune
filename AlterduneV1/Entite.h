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
    int mpMax; // je veux rajouter les MP pour les sorts plus tardboule de feux et paralsysie (1 tour sur 2 le monstre ne peut pas attaquer)
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
    int getForce() const 
    { 
        return force; 
    }
    int getDefense() const 
    { 
        return defense;
    }
    void setHP(int nouveauHP) 
    {
    if (nouveauHP > hpMax) hp = hpMax;
    else if (nouveauHP < 0) hp = 0;
    else hp = nouveauHP;
    }
};
#endif