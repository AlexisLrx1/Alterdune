#include "LectureCSV.h"

vector<string> LectureCSV::split(const string& str, char sep) 
{
    vector<string> resultat;
    stringstream chaine(str);
    string item;
    while (getline(chaine, item, sep)) {
        resultat.push_back(item);
    }
    return resultat;
}
void LectureCSV::chargerItems(const string& fichier, Joueur& joueur) 
{
    ifstream file(fichier);
    if (!file.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier: " << fichier << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tab = split(line, ';');
        if (tab.size() >= 4) { 
            Item item;
            item.nom = tab[0];
            item.type = tab[1];
            item.valeur = stoi(tab[2]); 
            item.quantite = stoi(tab[3]);
            item.rarete ="commun";
            joueur.AjouterItem(item);
        }
    }
    file.close();
}

vector<Monstre> LectureCSV::chargerMonstres(const string& fichier)
{
    vector<Monstre> bestiaire;
    ifstream file(fichier);
    string ligne;
    if (!file.is_open()) 
    {
        return bestiaire;
    }
    while (getline(file, ligne)) 
    {
        if (ligne.empty()) continue;
        
        vector<string> tab = split(ligne, ';');
        if (tab.size() >= 7) 
        {
            string cat = tab[0];    
            string nom = tab[1];     
            int h = stoi(tab[2]);    
            int f = stoi(tab[3]);    
            int d = stoi(tab[4]);    
            int mGoal = stoi(tab[5]); 
            int Xp  = stoi(tab[6]);  
            
            Monstre m( cat, nom, h, f, d, mGoal, Xp);
            m.setXpDonne(Xp);
            bestiaire.push_back(Monstre(cat, nom, h, f, d, mGoal, Xp));

        }
    }
    file.close();
    return bestiaire;
}

TableActions LectureCSV::chargerActions(const string& fichier) 
{
    TableActions table;
    ifstream file(fichier);
    string ligne;

    if (!file.is_open()) {
        cout << "Erreur : Impossible d'ouvrir " << fichier << endl;
        return table;
    }

    while (getline(file, ligne)) 
    {
        if (ligne.empty()) continue;
        stringstream ss(ligne);
        string nomMonstre, nomAction, pointsStr, message;
        getline(ss, nomMonstre, ';');
        getline(ss, nomAction, ';');
        getline(ss, pointsStr, ';');
        getline(ss, message, ';');

        if (!nomMonstre.empty() && !nomAction.empty())
        {
            ResultatAction resultat;
            resultat.points = stoi(pointsStr);
            resultat.message = message;
            table[nomMonstre][nomAction] = resultat;
        }
    }
    file.close();
    return table;
}


