#include "Combat.h"
#include "couleurs.h"
#include "style.h"

Combat::Combat(Joueur& j ,Monstre& m,TableActions& ta) : joueur(j), monstre(m), tableActions(ta) {}

void Combat::LancerCombat() 
{
    style::LogoFight();
    monstre.setRencontre(true);
    if (monstre.getCategorie() == "BOSS")
    {
        cout << RED << BOLD << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << RESET << endl;
        cout << RED << BOLD << "   ALERTE : BOSS " << monstre.getName() << "   " << RESET << endl;
        cout << RED << BOLD << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << RESET << endl;
    }
    else if (monstre.getCategorie() == "MINIBOSS") 
    {
        cout << YELLOW << BOLD << "ATTENTION : " << monstre.getName() << " approche ! \n" << RESET << endl;
    } 
    else
    {
        cout << "Un " << monstre.getName() << " apparait !" << endl;
    }

    while (joueur.getHP() > 0 && monstre.getHP() > 0 ) 
    {
        afficherBarreVie(joueur.getName(), joueur.getHP(), joueur.getHPMax(), BG_GREEN);
        afficherBarreVie(monstre.getName(), monstre.getHP(), monstre.getHPMax(), BG_RED);
        afficherBarreSimple(monstre.getMercy(), 100,  BG_BRIGHT_YELLOW);
        afficherMenuCombat();
        int choix;
        if (!(cin >> choix)) 
        {
            cout << RED << "Entree invalide ! Tapez un nombre plutôt." << RESET << endl;
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            continue; 
        }

        if (choix == 1)
        {
            menuAttaque();
            if (monstre.getHP() <= 0) return;
        } 
        else if (choix == 2) menuAct();
        else if (choix == 3) menuItems();
        else if (choix == 4) menuMercy();
        else if (choix == 5) {
        Fuite();
        break; 
        }
        if (monstre.getHP() > 0 && !monstre.estEpargnable()) {
            tourMonstre();
        }

    }
    monstre.setHP(monstre.getHPMax());
}

void Combat::afficherMenuCombat()
 {
    cout << "\nA toi de jouer " << joueur.getName() << "!" << endl;
    cout << "HP restant : " << joueur.getHP() << " | Hp du monstre restant : " << monstre.getHP() << endl;
    cout << "\n1. Attaquer le monstre" <<  "\n2. Choisir de le persuader"<< "\n3. Inventaire des sorts"<<"\n4. Coup de grâce! (Mercy à 100)" <<"\n5. décder de fuire...." << endl;
    cout << "Quellle action choisis-tu ? ";
}


void Combat::menuAttaque()
{
    int degats = rand() % (monstre.getHPMax() + 1);
    monstre.recevoirDegats(degats);
    cout << "Vous attaquez et faites " << degats << " points de dégats" << endl;
    if (monstre.getHP() <= 0)
    {
        cout << GREEN << "Victoire ! Vous avez vaincu " << monstre.getName() << RESET << endl;
        if ((rand() % 100) < 30)
         {
                bool dropUnique = false; 
                if (dropUnique) 
                {
                    cout << MAGENTA << "INCROYABLE ! " << monstre.getName() << " a lache un objet unique !" << RESET << endl;
                } 
                else
                {
                      joueur.dropAleatoire();
                }
         }
        joueur.gagnerCombat(true);
        int xpGagne = monstre.getXpDonne(); 
        joueur.ajouterXP(xpGagne);
        monstre.estMort();
    }
}

void Combat::menuAct()
{
    string choix;
    cout << "\nVoici les actions disponibles : " << endl;
    cout << "INSULT, PRIER, MIAM, BOITER, AGENOUILLER, MENACER" << endl;
    cout << "IMMOBILE, BOULEDENEIGE, CAILLOU, GRRRGAGAGAG, CRIER, MOOH, GLAGLA, GROIN" << endl;
    cout << "\nQuelle action faire ? (Ecrivez le nom en MAJUSCULE) : ";
    cin >> choix;
    string nomMonstre = monstre.getName();

    if (tableActions[nomMonstre].count(choix)) {

        ResultatAction res = tableActions[nomMonstre][choix];
        cout << "\n" << res.message << endl;
        monstre.modifierMercy(res.points);

        if (res.points > 0) {
            cout << "[MERCY + " << res.points << "] Le monstre semble sensible a votre action." << endl;
        } else if (res.points < 0) {
            cout << "[MERCY " << res.points << "] Oups... Il n'a pas aime du tout !" << endl;
        }
    } 
    else {
        cout << "\nVous tentez " << choix << "... mais le " << nomMonstre << " vous regarde bizarrement." << endl;
        cout << "Ca n'a aucun effet." << endl;
    }
    
}
void Combat::menuItems() 
{
    joueur.AfficherInventaire();
    int choix;
    cout << "Utiliser quel objet (0 pour annuler) ? ";
    cin >> choix;
    if (choix > 0) {
        joueur.UtiliserItem(choix - 1, &monstre);
    }
}
 void Combat::menuMercy() 
 {
        if (monstre.estEpargnable()) {
            cout << "Vous epargnez " << monstre.getName() << ". Le combat finit pacifiquement." << endl;
            monstre.setHP(0);
            joueur.gagnerCombat(false); 
            monstre.modifierMercy(-100);
        } 
        else {
            cout << "Le monstre ne veut pas encore s'arreter !" << endl;
        }
    }
void Combat::Fuite() 
{
    if (monstre.getCategorie() == "BOSS")
     {
        cout << "Impossible de fuir face a un BOSS voyons!" << endl;
    } 
    else
    {
        cout << "Vous prenez la fuite..." << endl;
        joueur.compteurFuite();
    }
}
void Combat::tourMonstre()
{
    cout << "\nC'est au tour du monstre !" << endl;
    int degats =  rand() % (joueur.getHPMax()  /  4 + 1) + joueur.getForce() / 2;
    joueur.recevoirDegats(degats);
}

void Combat::afficherBarreVie(string nom, int hp, int hpMax, string couleurFond)
{
    int largeurBarre = 20; 
    float ratio = (hpMax > 0) ? (float)hp / hpMax : 0;
    int remplissage = (int)(ratio * largeurBarre);

    cout << nom << " [" << hp << "/" << hpMax << "] " << endl;
    cout << couleurFond; 
    for (int i = 0; i < remplissage; i++)
    {
        cout << " " ; 
    }

    cout << BG_GRAY;  
    for (int i = 0; i < (largeurBarre - remplissage); i++) {
        cout << " "; 
    }
    
    cout << RESET << " HP" << endl;
}
void Combat::afficherBarreSimple(int actuel, int max, string couleurFond) {
    int largeurBarre = 18; 
    float ratio = (max > 0) ? (float)actuel / max : 0;
    if (ratio > 1) ratio = 1;

    int remplissage = (int)(ratio * largeurBarre);
    cout << couleurFond; 
    for (int i = 0; i < remplissage; i++) {
        cout << " "; 
    }
    cout << BG_GRAY; // Fond gris pour la partie vide
    for (int i = 0; i < (largeurBarre - remplissage); i++) {
        cout << " "; 
    }
    
    cout << RESET <<  "   Mercy" << endl;
}