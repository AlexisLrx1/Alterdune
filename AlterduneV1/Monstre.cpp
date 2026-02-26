#include "Monstre.h"
#include <iostream>
#include <algorithm>

using namespace std;

Monstre::Monstre(string cat, string nom, int h, int f, int d, int mGoal)
: Entite(nom,h,0,f,d) , categorie(cat) , mercyGoal(mGoal) {
    mercyGauge = 0;
}

void Monstre::ajouterAction(string idAction) {
    actActions.push_back(idAction);
}

void Monstre::modifierMercy(int valeur) {
    mercyGauge += valeur;
    if (mercyGauge < 0)
    {
        mercyGauge = 0;
    }
    if (mercyGauge > 100)
    {
        mercyGauge = mercyGoal;
    }
    cout << "La jauge MERCY est maintenant à " << mercyGauge << "%, Epargnez-le! " << endl;
}

bool Monstre::estEpargnable() const {
    return mercyGauge >= mercyGoal;
}

void Monstre::afficherActions() const {
    cout << "Actions ACT disponibles pour " << name << " (" << categorie << ") :" << endl;
    for (size_t i = 0; i < actActions.size(); ++i) {
        cout << i + 1 << ". " << actActions[i] << endl;
    }
}

void Monstre::afficherInfosBestiaire(bool estTue) const {
    cout << "--- " << name << " ---" << endl;
    cout << "Categorie : " << categorie << endl; 
    cout << "Stats Finales : HP Max " << hpMax << " | ATK " << force << " | DEF " << defense << endl;
    cout << "Resultat : " << (estTue ? "TUE" : "EPARGNE") << endl;
}
bool Monstre::ComporteAct(string actionJoueur) const {
    for (const string& action : actActions) {
        if (action == actionJoueur) {
            return true;
        }
    }
    return false;
}