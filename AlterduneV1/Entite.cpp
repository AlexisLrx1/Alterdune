#include "Entite.h"
#include "couleurs.h"
#include <algorithm>

using namespace std;
Entite::Entite(string n, int h, int m, int f, int d) 
: name(n), hp(h), hpMax(h), mp(m), mpMax(m), force(f), defense(d) {}

void Entite::recevoirDegats(int degats)
 {
    if (degats <= defense) 
    {
        cout << name << " a bloqué l'attaque ..." << endl;
        hp -= 0;
        return;
    }
    if (degats > 10000) 
    {
        cout << name << " le monstre vous salue et vous souhaite une bonne journée !" << endl;
        hp = 0; 
        return;
    }
    hp -= degats - defense;
    if (hp < 0) {
        hp = 0;
    }
    if (hp < 0) {
        hp = 0;
    }
    if (degats == 0) {
        cout << name << " a esquive l'attaque !" << endl;
    } 
    else {
        cout << RED << name << " a recu " << degats << " points de degats." << RESET << endl;
    }
    if (hp == 0) {
        cout << RED << name << " est hors d'état de nuire!" << RESET << endl;
    }
}
