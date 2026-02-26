#ifndef COMBAT_H
#define COMBAT_H

#include "Joueur.h"
#include "Monstre.h"

class Combat {
    private:
    Joueur& joueur;
    Monstre& monstre;

    public:
    Combat(Joueur& j ,Monstre& m);
    void LancerCombat();


private:
    void menuAttaque();
    void menuAct();
    void menuItems();
    void menuMercy();
    void Fuite();
    void tourMonstre();
    void afficherMenuCombat();
};

#endif
