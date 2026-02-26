#include "Combat.h"
Combat::Combat(Joueur& j ,Monstre& m) : joueur(j), monstre(m) {}
void Combat::LancerCombat() {
    monstre.setRencontre(true);
    cout << "\n[ !!! TRANSITION ECRAN NOIR !!! ]" << endl;
    cout << "Un " << monstre.getName() << " apparait !" << endl;

    while (joueur.getHP() > 0 && monstre.getHP() > 0) {
        afficherMenuCombat();
        int choix;
        cin >> choix;

        if (choix == 1) menuAttaque();
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
}
void Combat::afficherMenuCombat() {
    cout << "\n--- TOUR DE " << joueur.getName() << " ---" << endl;
    cout << "HP: " << joueur.getHP() << " | Monstre HP: " << monstre.getHP() << endl;
    cout << "1. ATTAQUE | 2. ACT | 3. ITEM | 4. MERCY | 5. FUITE" << endl;
    cout << "Choix : ";
}


void Combat::menuAttaque() {
    int degats = rand() % (monstre.getHPMax() + 1);
    monstre.recevoirDegats(degats);
    cout << "Vous attaquez et faites " << degats << " points de dégats" << endl;
    if (monstre.getHP() <= 0) {
        cout << "Victoire ! Vous avez vaincu " << monstre.getName() << endl;
        joueur.gagnerCombat(true);
    }
}
void Combat::menuAct() {
    monstre.afficherActions();
    string choix;
    cout << "Quelle action faire ?Selectionnez le numero du dialogue choisi : ";
    cout << "INSULT | PRIER | MIAM | BOITER | AGENOUILLER | MENACER" << endl;
    cout << "IMMOBILE | BOULEDENEIGE | CAILLOU | GRRRGAGAGAG | CRIER" << endl;
    cin >> choix;
    
    if (monstre.ComporteAct(choix))
    {
        cout << "Vous parlez au" << monstre.getName()<< ", il semble apprécier!" << endl;
        monstre.modifierMercy(50);
    }
    else 
    {
        cout << "Ca n'a aucun effet sur ce monstre..." << endl;
    }
}
    void Combat::menuItems() {
    joueur.AfficherInventaire();
    int choix;
    cout << "Utiliser quel objet (0 pour annuler) ? ";
    cin >> choix;
    if (choix > 0) {
        joueur.UtiliserItem(choix - 1);
    }
}
    void Combat::menuMercy() {
        if (monstre.estEpargnable()) {
            cout << "Vous epargnez " << monstre.getName() << ". Le combat finit pacifiquement." << endl;
            monstre.recevoirDegats(monstre.getHP()); // On force la fin du combat
            joueur.gagnerCombat(false); // false = épargné
        } 
        else {
            cout << "Le monstre ne veut pas encore s'arreter !" << endl;
        }
    }
void Combat::Fuite() {
    if (monstre.getCategorie() == "BOSS") {
        cout << "Impossible de fuir face a un BOSS voyons!" << endl;
    } else {
        cout << "Vous prenez la fuite..." << endl;
    }
}
void Combat::tourMonstre() {
    cout << "\n--- TOUR DU MONSTRE ---" << endl;
    int degats = rand() % 10 + 1; 
    joueur.recevoirDegats(degats);
}