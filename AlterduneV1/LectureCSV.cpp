#include "LectureCSV.h"

vector<string> LectureCSV::split(const string& str, char sep) {
    vector<string> resultat;
    stringstream stringS(str);
    string item;

    while (getline(stringS, item, sep)) {
        resultat.push_back(item);
    }
    return resultat;
}
void LectureCSV::chargerItems(const string& fichier, Joueur& joueur) {
    ifstream file(fichier);
    if (!file.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier: " << fichier << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tab = split(line, ';');
        if (tab.size() >= 4) { // il faut nom,type,valeur et quantite
            Item item;
            item.nom = tab[0];
            item.type = tab[1];
            item.valeur = stoi(tab[2]); // convertit la valeur en entier
            item.quantite = stoi(tab[3]);
            item.rarete ="commun";
            joueur.AjouterItem(item);
        }
    }
    file.close();
}

vector<Monstre> LectureCSV::chargerMonstres(const string& fichier) {
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
        
        vector<string> tokens = split(ligne, ';');
        if (tokens.size() >= 7) 
        {
            string cat = tokens[0];     // CATEGORIE 
            string nom = tokens[1];     // NOM 
            int h = stoi(tokens[2]);    // HP 
            int f = stoi(tokens[3]);    // FORCE (ATK) 
            int d = stoi(tokens[4]);    // DEFENSE 
            int mGoal = stoi(tokens[5]); // MERCY GOAL
            int Xp  = stoi(tokens[6]);  // XP DONNE
            
            Monstre m( cat, nom, h, f, d, mGoal, Xp);
            m.setXpDonne(Xp);
            
            bestiaire.push_back(Monstre(cat, nom, h, f, d, mGoal, Xp));


        }
    }
    file.close();
    return bestiaire;
}
TableActions LectureCSV::chargerActions(const string& fichier) {
    TableActions table;
    ifstream file(fichier);
    string ligne;

    if (!file.is_open()) {
        cout << "Erreur : Impossible d'ouvrir " << fichier << endl;
        return table;
    }

    while (getline(file, ligne)) {
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string nomMonstre, nomAction, pointsStr, message;
        getline(ss, nomMonstre, ';');
        getline(ss, nomAction, ';');
        getline(ss, pointsStr, ';');
        getline(ss, message, ';');

        if (!nomMonstre.empty() && !nomAction.empty())
        {
            ResultatAction res;
            res.points = stoi(pointsStr);
            res.message = message;
            table[nomMonstre][nomAction] = res;
        }
    }
    file.close();
    return table;
}
std::vector<std::vector<int>> LectureCSV::chargerMap(const std::string& fichier) {
    std::vector<std::vector<int>> map;
    std::ifstream file(fichier);
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        std::string value;

        while (std::getline(ss, value, ',')) { // On sépare par la virgule
            row.push_back(std::stoi(value));
        }
        map.push_back(row);
    }
    return map;
}


