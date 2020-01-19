/*
 * File:   util.cpp
 * Author: Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 * Labo 5
 *
 * Description: Utilitaires nécessaires au correcteur orthographique.
 */

#include "Util.h"

bool stringToLower(std::string& str){
    for(char &c : str){
        if(isdigit(c)){
            return false;
        }
        c = tolower(c);
    }
    return true;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        if(ch == '\'')
            return false;
        return !std::isspace(ch);
    }));
}

inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        if(ch == '\'')
            return false;
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void lectureDonnees(const std::string filename, std::list<std::string>& donnees){
    std::string line;
    bool hasNoDigit = false;
    std::ifstream s(filename);
    while (std::getline(s, line)) {
        std::vector<std::string> elements = split(line, ' ');
        for(std::string element : elements){
            trim(element);
            //Split à nouveau la châine mais cette fois-ci seulement si des - sont présents
            //Ainsi il est possible de vérifier l'orthographe de mot composé
            std::vector<std::string> elements2 = split(element, '-');
            for(std::string element2 : elements2){
                hasNoDigit = stringToLower(element2);
                //Va enlever tout les carcatère qui ne sont pas alphanumériques de la chaîne element2
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

void methode1(const std::string& str, std::list<std::string>& perm) {
    for (size_t i = 0; i < str.length(); ++i) {
        std::string s = str;
        s.erase(std::remove(s.begin() + i, s.begin() + i + 1, s[i]));
        perm.push_back(s);
    }
}

void methode2(const std::string& str, std::list<std::string>& perm) {
    for (size_t i = 0; i <= str.length(); ++i) {
        for (char j = 'a'; j <= 'z'; ++j) {
            std::string s = str;
            s.insert(s.begin() + i, j);
            perm.push_back(s);
        }
    }
}

void methode3(const std::string& str, std::list<std::string>& perm) {
    for (size_t i = 0; i < str.length(); ++i) {
        for (char j = 'a'; j <= 'z'; ++j) {
            std::string s = str;
            s[i] = j;
            perm.push_back(s);
        }
    }
}

void methode4(const std::string& str, std::list<std::string>& perm) {
    for (size_t i = 0; i < str.length(); i += 2) {
        std::string s = str;
        std::swap(s[i], s[i + 1]);
        perm.push_back(s);
    }
}
