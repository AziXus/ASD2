/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: stéphane
 *
 * Created on January 10, 2020, 1:57 PM
 */

#include <chrono>
#include "Dictionary.h"
#include "Util.h"

using namespace std;

#define DICTIONARY "dictionary.txt"
#define INPUT_FILE "input_sh.txt"
#define USE_TST

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

