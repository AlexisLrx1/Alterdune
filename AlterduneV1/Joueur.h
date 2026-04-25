#ifndef JOUEUR_H
#define JOUEUR_H

#include "Entite.h"
#include <vector>

struct Item {
    string nom;
    string type;
    int valeur; 
    int quantite; 
    string rarete; 
};

class Joueur : public Entite {
private:
    // Stat perso
    int niveau;
    int xp;
    int MonstresFuit;
    int nbVictoires;
    int nbMeurtres = 0;
    int nbEpargnes = 0;

    // inventaire (on utilise vector)
    vector<Item> inventaire;

    // Equipemen Armure et Arme
    string armeNom;
    int bonusDegats;
    string armureNom;
    int bonusDefense;
    void monterNiveau();
    

public:
    Joueur(string n);
    void AjouterItem(Item item);
    void UtiliserItem(int index);
    void AfficherStats();
    void AfficherInventaire();
    void ajouterXP(int montant);
    int getNbVictoires() const 
    { 
        return nbVictoires; 
    }
    void gagnerCombat(bool combatGagne);
    int getNbMeurtres() const 
    { 
        return nbMeurtres;
    }
    int getnbEpargnes() const 
    { 
        return nbEpargnes; 
    }
    void dropItem(string nomItem, string type, int valeur);
    void dropAleatoire() ;
};
#endif
