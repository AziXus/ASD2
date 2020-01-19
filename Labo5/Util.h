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

/*
 * @param str   une chaîne de caractères
 * @return  true si la chaîne ne contient pas de caractère numérique et a été passée en minuscules, false sinon
 */
bool stringToLower(std::string& str);

#endif /* UTIL_H */

