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

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <chrono>
#include <list>
#include <unordered_set>
#include "Dictionary.h"

using namespace std;

std::list<string> donnees;

/*
 * @brief
 *
 * @param s     une chaîne de caractères
 * @param delim le caractère de délimitation
 * @param elems le vecteur d'éléments extraits de la chaîne de caractères
 */
vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

vector<std::string> splitInterne(const std::string &s, char delim[], size_t size) {
    std::vector<std::string> elems;
    for(int i = 0; i < size; i++){
        split(s, delim[i], elems);
    }
    return elems;
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        if(ch == '\'')
            return false;
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        if(ch == '\'')
            return false;
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void lectureDonnees(string filename){
        std::string line;
        // '—'
        char delims[] = {' ', '-', '[', ']'};
        size_t size = 3;
        bool hasNoDigit = false;
        std::ifstream s(filename);
        while (std::getline(s, line)) {
            std::vector<string> elements = split(line, ' ');
            for(string element : elements){
                trim(element);
                std::vector<string> elements2 = split(element, '-');
                for(string element2 : elements2){
                    hasNoDigit = stringToLower(element2);
                    element2.erase(std::remove_if(element2.begin(), element2.end() 
                    ,[] (char c) { 
                        return c != '\'' && !isalpha(c);
                    }), element2.end());
                    trim(element2);

                    if(hasNoDigit && !element2.empty())
                        donnees.push_back(element2);
                    hasNoDigit = true;
                }
            }
        }
        s.close();
}

void methode1(const string& str, list<string>& perm) {
    for (size_t i = 0; i < str.length(); ++i) {
        string s = str;
        s.erase(std::remove(s.begin() + i, s.begin() + i + 1, s[i]));
        perm.push_back(s);
    }
}

void methode2(const string& str, list<string>& perm) {
    for (size_t i = 0; i <= str.length(); ++i) {
        for (char j = 'a'; j <= 'z'; ++j) {
            string s = str;
            s.insert(s.begin() + i, j);
            perm.push_back(s);
        }
    }
}

void methode3(const string& str, list<string>& perm) {
    for (size_t i = 0; i < str.length(); ++i) {
        for (char j = 'a'; j <= 'z'; ++j) {
            string s = str;
            s[i] = j;
            perm.push_back(s);
        }
    }
}

void methode4(const string& str, list<string>& perm) {
    for (size_t i = 0; i < str.length(); i += 2) {
        string s = str;
        swap(s[i], s[i + 1]);
        perm.push_back(s);
    }
}

#define DICTIONARY "dictionary.txt"
#define INPUT_FILE "input_wikipedia.txt"
#define USE_TST

int main() {
    lectureDonnees(INPUT_FILE);
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

    std::cout << "Temps de creation du dico:  " << dico.getCreation() << " microseconds" << std::endl;
    std::cout << "Temps de search du dico:  " << dico.getSearch() << " microseconds" << std::endl;
    return 0;
}

