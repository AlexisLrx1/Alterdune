#ifndef COMBAT_H
#define COMBAT_H

#include "LectureCSV.h"
#include "Joueur.h"
#include "Monstre.h"

class Combat {
    private:
    Joueur& joueur;
    Monstre& monstre;
    TableActions& tableActions;

    public:
    Combat(Joueur& j ,Monstre& m,TableActions& ta) ;
    void LancerCombat();


private:
    void menuAttaque();
    void menuAct();
    void menuItems();
    void menuMercy();
    void Fuite();
    void tourMonstre();
    void afficherMenuCombat();
    void afficherBarreVie(string nom, int hp, int hpMax, string couleur);
    void afficherBarreSimple(int actuel, int max, string couleur);
};

#endif
