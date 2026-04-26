#ifndef LECTURECSV_H
#define LECTURECSV_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>  
#include <sstream> 
#include <map>
#include "Joueur.h"
#include "Monstre.h"

using namespace std;

struct ResultatAction 
{
    int points;
    string message;
};

using TableActions = map<string, map<string, ResultatAction>>; // trop long a ecrire donc on fait un alias pour simplifier pour taper.


class LectureCSV {
public:
    static void chargerItems(const string& fichier, Joueur& joueur);
    static vector<Monstre> chargerMonstres(const string& fichier);
    static TableActions chargerActions(const string& fichier);
    static vector<string> split(const string& str, char sep);
};

#endif