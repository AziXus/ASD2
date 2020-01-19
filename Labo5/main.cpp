/*
 * File:   main.cpp
 * Author: Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 * Labo 5
 *
 * Description: Main de l'application correcteur orthographique. Lit un fichier et génère des propositions de
 * corrections des mots mal orthographiés (non présents dans le dictionnaire).
 * 
 * Temps pour l'arbre avec l'implémentation TST : 
 * 
 * Temps de chargement du dico                  :  879273 microseconds
 * Temps pour produire le resultat final du dico:  77687 microseconds
 * 
 * Temps pour l'arbre avec l'implémentation STL : 
 * 
 * Temps de chargement du dico                  :  453632 microseconds
 * Temps pour produire le resultat final du dico:  66967 microseconds
 * 
 */

#include <chrono>
#include "Dictionary.h"
#include "Util.h"

using namespace std;

#define DICTIONARY "dictionary.txt"
#define INPUT_FILE "input_sh.txt"
#define USE_TST     //Commenter/dé-commenter pour passer d'un dictionnaire TST à STL

int main() {
    std::list<string> donnees;
    lectureDonnees(INPUT_FILE, donnees);
    ofstream myfile;
    myfile.open("correct.txt");

#ifdef USE_TST
    DicoTST dico(DICTIONARY);
#else
    DicoSTL dico(DICTIONARY);
#endif
    list<string> perm;
    for (const string& d : donnees) {
        if (dico.contains(d))
            continue;

        myfile << "*" << d << endl;
        methode1(d, perm);
        for (const string& p : perm) {
            if (dico.contains(p)) {
                myfile << "1:" << p << endl;
            }
        }

        perm.clear();
        methode2(d, perm);
        for (const string& p : perm) {
            if (dico.contains(p)) {
                myfile << "2:" << p << endl;
            }
        }

        perm.clear();
        methode3(d, perm);
        for (const string& p : perm) {
            if (dico.contains(p)) {
                myfile << "3:" << p << endl;
            }
        }

        perm.clear();
        methode4(d, perm);
        for (const string& p : perm) {
            if (dico.contains(p)) {
                myfile << "4:" << p << endl;
            }
        }

    }

    std::cout << "Temps de chargement du dico                  :  " << dico.getCreation() << " microseconds" << std::endl;
    std::cout << "Temps pour produire le resultat final du dico:  " << dico.getSearch() << " microseconds" << std::endl;
    return 0;
}

