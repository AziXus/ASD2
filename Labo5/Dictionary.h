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
#include <unordered_set>
#include "Util.h"
#include "TernarySearchTree.h"

class Dictionary {
public:
    Dictionary(std::string filename){
        genererDico(filename);
    }
    
    void genererDico(std::string filename){
        std::string line;
        bool hasNoDigit = false;
        std::ifstream s(filename);
        while (std::getline(s, line)) {
            hasNoDigit = stringToLower(line);
            if(hasNoDigit)
                insert(line);
        }
        s.close();
    }
    
    virtual void insert(std::string str);
    
    virtual bool contains(std::string str);
};

class DicoStl : public Dictionary {
public:
    DicoStl(std::string filename):Dictionary(filename){
        
    }
  
    void insert(std::string str){
        dico.insert(str);
    }
    
    bool contains(std::string str){
        return dico.find(str) != dico.end();
    }
    
private:
    std::unordered_set<std::string> dico;
};

class DicoTST : public Dictionary {
public:
    DicoTST(std::string filename):Dictionary(filename){
        
    }
  
    void insert(std::string str){
        dico.put(str);
    }
    
    bool contains(std::string str){
        return dico.contains(str);
    }
    
private:
    TernarySearchTree dico;
};

#endif /* DICTIONARY_H */

