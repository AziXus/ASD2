/*
 * File:   util.h
 * Author: Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 * Labo 5
 *
 * Description: Utilitaires nécessaires au correcteur orthographique.
 */

#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include <algorithm>

/**
 * @param str   une chaîne de caractères
 * @return  true si la chaîne ne contient pas de caractère numérique et a été passée en minuscules, false sinon
 */
bool stringToLower(std::string& str);

/**
 * @brief Extrait des mots d'un string selon un caractère de délimitation donné
 *
 * @param s     une chaîne de caractères
 * @param delim le caractère de délimitation
 * @return les mots extraits de la chaîne de caractères sous la forme d'un vecteur de string
 */
std::vector<std::string> split(const std::string &s, char delim);

/**
 * @brief trim from start (in place)
 *
 * @param s     une chaîne de caractères
 */
inline void ltrim(std::string &s);

/**
 * @brief trim from end (in place)
 *
 * @param s     une chaîne de caractères
 */
inline void rtrim(std::string &s);

/**
 * @brief trim from both ends (in place)
 *
 * @param s     une chaîne de caractères
 */
inline void trim(std::string &s);

/**
 * @brief Extrait les mots d'un fichier.
 *
 * @param filename  le nom du fichier à lire
 * @param donnees   la liste de mots extraits du fichier
 */
void lectureDonnees(std::string filename, std::list<std::string>& donnees);

/**
 * @brief Génére toutes les combinaisons d'un mot orthographié.
 * Méthode 1 : il y a une lettre en trop.
 *
 * @param str   un mot
 * @param perm  la liste des combinaisons possibles
 */
void methode1(const std::string& str, std::list<std::string>& perm);

/**
 * @brief Génére toutes les combinaisons d'un mot orthographié.
 * Méthode 2 : il manque une lettre.
 *
 * @param str   un mot
 * @param perm  la liste des combinaisons possibles
 */
void methode2(const std::string& str, std::list<std::string>& perm);

/**
 * @brief Génére toutes les combinaisons d'un mot orthographié.
 * Méthode 3 : une lettre a été mal saisie.
 *
 * @param str   un mot
 * @param perm  la liste des combinaisons possibles
 */
void methode3(const std::string& str, std::list<std::string>& perm);

/**
 * @brief Génére toutes les combinaisons d'un mot orthographié.
 * Méthode 4 : 2 lettres ont été interverties.
 *
 * @param str   un mot
 * @param perm  la liste des combinaisons possibles
 */
void methode4(const std::string& str, std::list<std::string>& perm);


#endif /* UTIL_H */

