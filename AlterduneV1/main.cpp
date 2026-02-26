
#include <iostream>
#include <iostream>
#include <ctime>
#include "Joueur.h"
#include "Monstre.h"
#include "LectureCSV.h"
#include "Combat.h"
using namespace std;

 // .\Alterdune.exe pour lancer le jeu 
 
void AfficherMenu() {
    cout << "\n--- MENU ALTERDUNE ---" << endl;
    cout << "1. Partir a l'aventure (Combat)" << endl;
    cout << "2. Voir mes Statistiques" << endl;
    cout << "3. Ouvrir l'Inventaire" << endl;
    cout << "4. Consulter l'Encyclopedie (Bestiaire)" << endl;
    cout << "5. Sauvegarder et Quitter" << endl;
    cout << "Choix : ";
}
int main() {
    srand(time(0));
    cout << "==========================================" << endl;
    cout << "   BIENVENUE DANS LE MONDE D'ALTERDUNE" << endl;
    cout << "==========================================" << endl;
    string nom;
    string genre;
    cout << "Entrez votre nom jeune aventurier :";
    cin >> nom;
    cout << "Choisissez votre genre (M/F/N) : ";
    cin >> genre;
    Joueur joueur(nom);
    // pallettes couleur plus tard
    LectureCSV::chargerItems("items.csv", joueur);
    vector<Monstre> bestiaire = LectureCSV::chargerMonstres("Monstres.csv");
    cout << "\nCa m'a l'air bon pour les bestioles!" << endl;
    cout << "Bienvenue sur la première ile d'alterdune : Les plaines verdoyantes!" << endl;
    int choix = 0;
 
    while (choix != 5 && joueur.getHP() > 0 && joueur.getNbVictoires() < 10) {
        AfficherMenu();
        cin >> choix;
        switch (choix) {
            case 1: { 
                int Aleatoire = rand() % bestiaire.size();
                cout << "\n[LANCEMENT D'UN COMBAT...]" << endl;
                Monstre &monstreDuBestiaire = bestiaire[Aleatoire];
                while (monstreDuBestiaire.getHP() <= 0) 
                {
                    Aleatoire = rand() % bestiaire.size();
                    monstreDuBestiaire = bestiaire[Aleatoire];
                }
                Combat combat(joueur, monstreDuBestiaire);
                combat.LancerCombat();
            }
                break; 
            case 2:
                joueur.AfficherStats();
                break;
            case 3:
                joueur.AfficherInventaire();
                break;
            case 4:
             
                cout << "\n--- ENCYCLOPEDIE ---" << endl;
                for (int i = 0; i < bestiaire.size(); i++) 
                {
                    if (bestiaire[i].aEteRencontre()) 
                    { // On ne l'affiche que si rencontré
                        bestiaire[i].afficherInfosBestiaire(false);
                    } 
                    else 
                    {
                    cout << "--- ??? --- (Monstre non rencontre)" << endl;
                    }
                }
            break;
            case 5:
            cout << "Sauvegarde et fermeture du jeu..." << endl;
            break;
            default:
            cout << "Ce choix marche pas c'st entre un et cinq pardi!" << endl;
            break;
        }
    }
    if (joueur.getNbVictoires() >= 10) {
        cout << "\nFélicitations ! Tu as terminé l'aventure." << endl;
        // Ici on ajoutera la logique : Pacifiste / Génocidaire / Neutre
    } 
    else if (joueur.getHP() <= 0) {
        cout << "\nGAME OVER" << endl;
        cout << "Fais mieux la prochaine fois." << endl;
    }
    if (joueur.getNbVictoires() >= 10) {
    cout << "\n=== BILAN DE VOTRE AVENTURE ===" << endl;
    if (joueur.getNbMeurtres() == 0) {
        cout << "FIN PACIFISTE : Vous n'avez fait de mal a personne. Le monde est en paix." << endl;
    } else if (joueur.getNbMeurtres() >= 10) {
        cout << "FIN GENOCIDAIRE : Il ne reste plus personne... Vous etes un monstre." << endl;
    } else {
        cout << "FIN NEUTRE : Vous avez fait des choix difficiles. L'equilibre est maintenu." << endl;
    }
    }
    return 0;
}