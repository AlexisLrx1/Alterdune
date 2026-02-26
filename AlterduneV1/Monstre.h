#ifndef MONSTRE_H
#define MONSTRE_H

#include "Entite.h"
#include <vector>

using namespace std;

class Monstre : public Entite {
private:
    string categorie; //mini boss ou boss ou normal
    int mercyGauge;   // Jauge actuelle (0 à 100) 
    int mercyGoal;
    vector<string> actActions;
    bool rencontre = false;
   

public:
    Monstre(string cat, string nom, int h, int f, int d, int mGoal);
    void modifierMercy(int valeur); 
    bool estEpargnable() const;
    void ajouterAction(string idAction);
    void afficherActions() const;
    string getCategorie() const { return categorie; }
    void afficherInfosBestiaire(bool estTue) const;
    bool ComporteAct(std::string actionJoueur) const;
    void setRencontre(bool etat) 
    { 
        rencontre = etat; 
    }
    bool aEteRencontre() const 
    { 
        return rencontre;
    }
};
#endif
