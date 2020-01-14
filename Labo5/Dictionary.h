/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dictionary.h
 * Author: stéphane
 *
 * Created on January 14, 2020, 1:06 PM
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "Util.h"

template <typename Struct>
class Dictionary {
public:
    Dictionary(std::string filename){
        std::string line;
        bool hasNoDigit = false;
        std::ifstream s(filename);
        while (std::getline(s, line)) {
            hasNoDigit = stringToLower(line);
            if(hasNoDigit)
                set.insert(line);
        }
        s.close();
    }
private:
    Struct<std::string> set;

};

#endif /* DICTIONARY_H */

