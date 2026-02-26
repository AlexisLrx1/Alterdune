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
            item.valeur = stoi(tab[2]); // ca convertit en entier
            item.quantite = stoi(tab[3]);
            item.rarete ="commun";
            joueur.AjouterItem(item);
        }
    }
    file.close();
}

vector<Monstre> LectureCSV::chargerMonstres(const string& filename) {
    vector<Monstre> listeMonstres;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ERREUR : Fichier " << filename << " introuvable ! Arret du jeu." << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        vector<string> tab = split(line, ';');
        if (tab.size() < 6) continue;
        Monstre m(tab[0], tab[1], stoi(tab[2]), stoi(tab[3]), stoi(tab[4]), stoi(tab[5]));
        for (int i = 6; i < tab.size(); i++) {
            if (tab[i] != "-" && !tab[i].empty()) {
                m.ajouterAction(tab[i]);
            }
        }
        listeMonstres.push_back(m);
    }
    file.close();
    return listeMonstres;
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

