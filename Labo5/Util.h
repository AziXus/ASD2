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
 * @brief Extrait des mots d'un string selon un caractère de délimitation donné
 *
 * @param s     une chaîne de caractères
 * @param delim le caractère de délimitation
 * @return les mots extraits de la chaîne de caractères sous la forme d'un vecteur de string
 */
std::vector<std::string> split(const std::string &s, char delim);

// trim from start (in place)
inline void ltrim(std::string &s);

// trim from end (in place)
inline void rtrim(std::string &s);

// trim from both ends (in place)
inline void trim(std::string &s);

void lectureDonnees(std::string filename, std::list<std::string>& donnees);

void methode1(const std::string& str, std::list<std::string>& perm);

void methode2(const std::string& str, std::list<std::string>& perm);

void methode3(const std::string& str, std::list<std::string>& perm);
/*
 *
 * test
 */
void methode4(const std::string& str, std::list<std::string>& perm);


#endif /* UTIL_H */

