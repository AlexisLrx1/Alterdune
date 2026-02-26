#include "Joueur.h"
#include <iostream>

using namespace std;

Joueur::Joueur(string n) : Entite(n, 100, 20, 10, 5) {
    niveau = 1;
    xp = 0;
    nbMeurtres = 0;
    nbEpargnes = 0;
    MonstresFuit = 0;
    nbVictoires = 0;
    // Equipement de base
    armeNom = "Epée en bois";
    bonusDegats = 0;
    armureNom = "Armure en cuir";
    bonusDefense = 2;
}
void Joueur::AfficherStats() {
    cout << "\n=== STATISTIQUES DE " << name << " ===" << endl;
    cout << "Niveau : " << niveau << " | HP : " << hp << "/" << hpMax << " | MP : " << mp << "/" << mpMax << endl; 
    cout << "Force : " << force << " | Defense : " << defense + bonusDefense << endl;
    cout << "Victoires : " << nbVictoires << "/10" << endl; 
    cout << "Monstres tues : " << nbMeurtres << " | Epargnes : " << nbEpargnes << endl;
    cout << "Fuites : " << MonstresFuit << endl;
    cout << "Equipement : " << armeNom << " & " << armureNom << endl;
    cout << "============================" << endl;
}
void Joueur::AfficherInventaire() {
    cout << "\n=== INVENTAIRE (" << inventaire.size() << "/20) ===" << endl; 
    if (inventaire.empty()) {
        cout << "Votre sac est vide." << endl;
    } else {
        for (int i = 0; i < inventaire.size(); i++) {
            cout << i + 1 << ". " << inventaire[i].nom << " [" << inventaire[i].rarete << "] x" 
                 << inventaire[i].quantite << " (" << inventaire[i].type << " +" << inventaire[i].valeur << ")" << endl;
        }
    }
}
void Joueur::UtiliserItem(int index) {
    if (index < 0 || index >= inventaire.size()) {
        cout << "Choix invalide." << endl;
        return;
    }
    Item &item = inventaire[index];
    if (item.type == "HEAL") {
        hp += item.valeur;
        if (hp > hpMax) hp = hpMax;
        cout << "Vous utilisez " << item.nom << " et recuperez " << item.valeur << " HP !" << endl;
    }
    // Tu pourras ajouter ici les MP ou les Somniferes plus tard
    
    item.quantite--;
    if (item.quantite <= 0) {
        inventaire.erase(inventaire.begin() + index); // Retire l'objet si plus de stock
    }
}

void Joueur::gagnerCombat(bool estTue) {
    nbVictoires++;
    if (estTue) 
    {
        nbMeurtres++;
        cout << "Vous avez elimine un ennemi." << endl;
    } 
    else 
    {
        nbEpargnes++;
        cout << "Vous avez agi avec compassion." << endl;
    }
}

void Joueur::AjouterItem(Item item) {
    inventaire.push_back(item);
    cout << "Objet ajoute : " << item.nom << endl;
}
