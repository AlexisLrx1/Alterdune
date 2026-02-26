#include "Entite.h"
#include <algorithm>

using namespace std;
Entite::Entite(string n, int h, int m, int f, int d) 
: name(n), hp(h), hpMax(h), mp(m), mpMax(m), force(f), defense(d) {}

void Entite::recevoirDegats(int degats) {
    hp -= degats;
    if (hp < 0) {
        hp = 0;
    }
    if (degats == 0) {
        cout << name << " a esquive l'attaque !" << endl;
    } 
    else {
        cout << name << " a recu " << degats << " points de degats." << endl; 
    }
    if (hp == 0) {
        cout << name << " est hors d'état de nuire!" << endl;
    }
}
