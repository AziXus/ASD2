/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Util.h
 * Author: stéphane
 *
 * Created on January 14, 2020, 1:19 PM
 */

#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include <algorithm>

/*#include <algorithm>
#include <functional>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <chrono>
#include <list>
#include <unordered_set>
#include "Dictionary.h"*/

/*
 * @param str   une chaîne de caractères
 * @return  true si la chaîne ne contient pas de caractère numérique et a été passée en minuscules, false sinon
 */
bool stringToLower(std::string& str);


/*
 * @brief
 *
 * @param s     une chaîne de caractères
 * @param delim le caractère de délimitation
 * @param elems le vecteur d'éléments extraits de la chaîne de caractères
 */
static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

static std::vector<std::string> splitInterne(const std::string &s, char delim[], size_t size) {
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

static void lectureDonnees(std::string filename, std::list<std::string>& donnees){
    std::string line;
    // '—'
    char delims[] = {' ', '-', '[', ']'};
    size_t size = 3;
    bool hasNoDigit = false;
    std::ifstream s(filename);
    while (std::getline(s, line)) {
        std::vector<std::string> elements = split(line, ' ');
        for(std::string element : elements){
            trim(element);
            std::vector<std::string> elements2 = split(element, '-');
            for(std::string element2 : elements2){
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

static void methode1(const std::string& str, std::list<std::string>& perm) {
    for (size_t i = 0; i < str.length(); ++i) {
        std::string s = str;
        s.erase(std::remove(s.begin() + i, s.begin() + i + 1, s[i]));
        perm.push_back(s);
    }
}

static void methode2(const std::string& str, std::list<std::string>& perm) {
    for (size_t i = 0; i <= str.length(); ++i) {
        for (char j = 'a'; j <= 'z'; ++j) {
            std::string s = str;
            s.insert(s.begin() + i, j);
            perm.push_back(s);
        }
    }
}

static void methode3(const std::string& str, std::list<std::string>& perm) {
    for (size_t i = 0; i < str.length(); ++i) {
        for (char j = 'a'; j <= 'z'; ++j) {
            std::string s = str;
            s[i] = j;
            perm.push_back(s);
        }
    }
}

static void methode4(const std::string& str, std::list<std::string>& perm) {
    for (size_t i = 0; i < str.length(); i += 2) {
        std::string s = str;
        std::swap(s[i], s[i + 1]);
        perm.push_back(s);
    }
}


#endif /* UTIL_H */

