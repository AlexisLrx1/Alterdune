#include "Joueur.h"
#include "couleurs.h"
#include <iostream>

using namespace std;

Joueur::Joueur(string n) : Entite(n, 100, 80, 10, 5) {
    niveau = 1;
    xp = 0;
    nbMeurtres = 0;
    nbEpargnes = 0;
    MonstresFuit = 0;
    nbVictoires = 0;
}
void Joueur::recevoirDegats(int degats)
 {
    if (degats <= defense) 
    {
        cout << name << " a bloqué l'attaque ..." << endl;
        hp -= 0;
        return;
    }
    hp -= degats - defense;
    if (hp < 0) 
    {
        hp = 0;
    }
    if (hp < 0)
     {
        hp = 0;
    }
    if (degats == 0) 
    {
        cout << name << " a esquive l'attaque !" << endl;
    } 
    else
    {
        cout << RED << name << " a recu " << degats << " points de degats." << RESET << endl;
    }
    if (hp == 0) 
    {
        cout << RED << name << " est hors d'état de nuire!" << RESET << endl;
    }
}
void Joueur::AfficherStats() 
{
    cout << "\n Statistique du joueur : " << name << " " << endl;
    cout << "Niveau : " << niveau << " | HP : " << hp << "/" << hpMax << " | MP : " << mp << "/" << mpMax << endl; 
    cout << "Force : " << force << " | Défense : " << defense << endl;
    cout << "Victoires : " << nbVictoires << "/10" << endl; 
    cout << "Monstres tués : " << nbMeurtres << " | Epargnés : " << nbEpargnes << endl;
    cout << "Fuites : " << MonstresFuit << endl;
    cout << "XP : " << xp << endl;
}
void Joueur::AfficherInventaire()
{
    cout << "\nInventaire : (" << inventaire.size() << "/20)" << endl; 
    if (inventaire.empty())
     {
        cout << "Votre sac est vide." << endl;
    } 
    else 
    {
        for (int i = 0; i < inventaire.size(); i++) {
            cout << i + 1 << ". " << inventaire[i].nom << " [" << inventaire[i].rarete << "] x" 
                 << inventaire[i].quantite << " (" << inventaire[i].type << " +" << inventaire[i].valeur << ")" << endl;
        }
    }
}
void Joueur::UtiliserItem(int index, Entite* cible) {
    if (index < 0 || index >= inventaire.size()) 
    {
        cout << "Choix invalide." << endl;
        return;
    }
    Item &item = inventaire[index];
    if (item.type == "HEAL")
     {
        hp += item.valeur;
        if (hp > hpMax) hp = hpMax;
        cout << "Vous utilisez " << item.nom << " et récuperez " << item.valeur << " PV !" << endl;
    }
    if (item.type == "SPELL" ) 
    {
        if (mp >= 50) 
        { 
            mp -= 50; 
            cout << "Vous lancez " << item.nom << " ! (Mana restant : " << mp << ")" << endl;

            if (cible) 
            {
                cible->recevoirDegats(item.valeur + cible->getDefense()); 
            }
            item.quantite--; 
        } 
        else 
        {
            cout << RED << "Pas assez de Mana ! (Requis : 50 | Actuel : " << mp << ")" << RESET << endl;
            return;
        }

        item.quantite--;
        if (item.quantite <= 0) 
        {
        inventaire.erase(inventaire.begin() + index);
        }
    }
}

void Joueur::gagnerCombat(bool estTue) {
    nbVictoires++;
    if (estTue) 
    {
        nbMeurtres++;
        cout << "Vous avez éliminé un ennemi." << endl;
    } 
    else 
    {
        nbEpargnes++;
        cout << "Vous avez agi avec compassion." << endl;
    }
}


void Joueur::AjouterItem(Item item) {
    inventaire.push_back(item);
    cout << "Objet ajouté : " << item.nom << endl;
}
void Joueur::ajouterXP(int montant)
 {
    xp += montant;
    cout << "Vous gagnez " << montant << " points d'expérience ! (Total: " << xp << ")" << endl;
    
    
    if (xp >= niveau * 100) {
        monterNiveau();
    }
 }

 void Joueur::monterNiveau() 
{
    niveau++;
    xp = 0;
    hpMax += 20;
    hp = hpMax; 
    force += 5;
    defense += 2;
    mpMax += 10;
    mp = mpMax;
    cout << GREEN << "\n LEVEL UP ! Vous êtes maintenant niveau " << niveau<< " ! " << RESET  <<endl;
}
void Joueur::dropItem(string nomItem, string type, int valeur) {
    for (auto &item : inventaire) {
        if (item.nom == nomItem) {
            item.quantite++;
            cout << YELLOW << "[DROP] Vous avez trouve un(e) " << nomItem << " supplémentaire !" << RESET << endl;
            return;
        }
    }
    Item nouvelItem;
    nouvelItem.nom = nomItem;
    nouvelItem.type = type;
    nouvelItem.valeur = valeur;
    nouvelItem.quantite = 1;
    nouvelItem.rarete = "Commun";
    
    inventaire.push_back(nouvelItem);
    cout << YELLOW << "[DROP] Nouveau butin : " << nomItem << " ajoute a l'inventaire !" << RESET << endl;
}
void Joueur::dropAleatoire() 
{
    vector<string> objetsPossibles = {"Potion", "Super Potion"};

    int index = rand() % objetsPossibles.size();
    string nomLoot = objetsPossibles[index];
    if (nomLoot == "Potion") dropItem("Potion", "HEAL", 15);
    else if (nomLoot == "Super Potion") dropItem("Super Potion", "HEAL", 30);
}