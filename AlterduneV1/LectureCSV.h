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

typedef map<string, map<string, ResultatAction>> TableActions;

class LectureCSV {
public:
    static void chargerItems(const string& fichier, Joueur& joueur);
    static vector<Monstre> chargerMonstres(const string& fichier);
    static TableActions chargerActions(const string& fichier);
    static vector<string> split(const string& str, char sep);
    static std::vector<std::vector<int>> chargerMap(const std::string& fichier);
};

#endif