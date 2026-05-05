#include "couleurs.h"
#include <iostream>
#include <iostream>
#include <ctime>
#include <map>
#include <windows.h>
#include "Joueur.h"
#include "Monstre.h"
#include "LectureCSV.h"
#include "Combat.h"
#include "style.h"
using namespace std;

 //g++ *.cpp -o Alterdune.exe pour compiler 
 // .\Alterdune pour lancer

void ClearScreen() 
{ 
    cout << "\033[2J\033[1;1H";
}
 
void AfficherMenu() 
{
    cout << "\n1) Partir a l'aventure (Combat)" << endl;
    cout << "2) Voir mes Statistiques" << endl;
    cout << "3) Ouvrir l'Inventaire" << endl;
    cout << "4) Consulter l'Encyclopedie (Bestiaire)" << endl;
    cout << "5) Sauvegarder et Quitter" << endl;
    cout << "Quel est votre choix ? : ";
}


int main() {
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);
    srand(time(0));
    ClearScreen();
    style::LogoAlterdune();
    cout << "Bienvenue dans Alterdune." << endl;
    string nom;
    string genre;
    cout << "Entrez votre nom jeune aventurier : ";
    cin >> nom;
    cout << "\n";
    ClearScreen();
    style::LogoGenre();
    cout << "êtes vous un jeune aventurier(M), aventurière(F) ou neutre(N) ? : ";
    cin >> genre;
    Joueur joueur(nom);
    LectureCSV::chargerItems("items.csv", joueur);
    vector<Monstre> bestiaire = LectureCSV::chargerMonstres("Monstres.csv");
    TableActions tableActions = LectureCSV::chargerActions("Actions.csv");
    cout << "\nCa m'a l'air bon pour les bestioles et leurs attaques!" << endl;
    cout << "Bienvenue sur la premiere ile d'alterdune : Les plaines verdoyantes!" << endl;
    int choix = 0;
    bool tue = false;
 
    while (choix != 5 && joueur.getHP() > 0 && joueur.getNbVictoires() < 10) 
    {
        AfficherMenu();
        if (!(cin >> choix)) 
        {
             cout << "Entree invalide ! Entrez un nombre." << endl;
             cin.clear(); 
             cin.ignore(10000, '\n'); 
             continue; 
        }
        ClearScreen();
        switch (choix) 
        {
            case 1:
           { 

                cout << "\n[LANCEMENT D'UN COMBAT...]" << endl;
                 int progression = joueur.getNbVictoires() + 1;
                 string cible = "NORMAL";
                 if (progression == 10) cible = "BOSS";
                 else if (progression == 5) cible = "MINIBOSS";
                 vector<int> selection;
                 for (int i = 0; i < bestiaire.size(); i++)
                  {
                        if (bestiaire[i].getCategorie() == cible)
                        {    
                                selection.push_back(i);
                        }
                 }

                 if (!selection.empty())
                 {
                    int indexAleatoire = selection[rand() % selection.size()];
                    Monstre& monstreCombat = bestiaire[indexAleatoire]; 
                    monstreCombat.setRencontre(true);
                    Combat combat(joueur, monstreCombat, tableActions); 
                    combat.LancerCombat();   
                }
                else
                {
                    cout << "Erreur : Aucun monstre de type " << cible << " trouvé dans le CSV !" << endl;
                }
                break;
           }
            case 2:
                joueur.AfficherStats();
                break;
            case 3:
                joueur.AfficherInventaire();
                break;
            case 4:

                cout << "\nBestiaire et leurs informations :" << endl;
                for (int i = 0; i < bestiaire.size(); i++) 
                {
                    if (bestiaire[i].aEteRencontre()) 
                    { 
                        if (bestiaire[i].infoTue()) 
                        {
                            bestiaire[i].afficherInfosBestiaire(true);
                        } 
                        else 
                        {
                            bestiaire[i].afficherInfosBestiaire(false);
                        }
                    } 
                    else 
                    {
                    cout << "   ???  (Monstre non rencontre)" << endl;
                    }
                }
            break;
            case 5:
            cout << "Sauvegarde et fermeture du jeu..." << endl;
            break;
            default:
            cout << "Ce choix marche pas c'est entre un et cinq pardi!" << endl;
            break;
        }
     }
    
    
    if (joueur.getNbVictoires() >= 10) 
    {
        cout << "\nFélicitations ! Tu as terminé l'aventure." << endl;
    } 
    else if (joueur.getHP() <= 0)
    {
        ClearScreen();
        cout << "\nTu as été vaincu... Mieux vaut se reposer et retenter l'aventure plus tard." << endl;
        style::LogoLose();

    }
    if (joueur.getNbVictoires() >= 10) 
    {
        cout << "\nVoici le bilan de votre aventure :" << endl;
        if (joueur.getNbMeurtres() == 0)
        {
            cout << "Fin PACIFISTE :  vous cherchez la paix et on vous remercie pour cela." << endl;
        } 
        else if (joueur.getNbMeurtres() >= 10) 
        {
        cout << "Fin GENOCIDAIRE : Tuer est votre seul source de satisfaction, qui est réellement le monstre...." << endl;
        } 
        else 
        {
        cout << "Fin  NEUTRE : Vos choix resultent en un bilan équilibré." << endl;
        }
    }
    return 0;
}