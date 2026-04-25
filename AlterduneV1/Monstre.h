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
    int xpDonne;
    int  compteur = 0;
    vector<string> actActions;
    bool rencontre = false;
      
public:
    Monstre(string cat, string nom, int h, int f, int d, int mGoal , int xp);
    void modifierMercy(int valeur); 
    bool estEpargnable() const;
    void ajouterAction(string idAction);
    string getCategorie() const { return categorie; }
    void afficherInfosBestiaire(bool estTue) const;
    bool ComporteAct(std::string actionJoueur) const;
    int getXpDonne() const { return xpDonne; }
    void setXpDonne(int montant) { xpDonne = montant; }
    void setRencontre(bool etat) 
    { 
        rencontre = etat; 
    }
    bool aEteRencontre() const 
    { 
        return rencontre;
    }
    int getCompteur() const 
    {
        return compteur;
    };
    void estMort() 
    {
        compteur++;
    }
    bool infoTue() const
    {
        return  compteur > 0;
    }
    int getMercy() const
    {
        return mercyGauge;
    }
}; 
#endif
