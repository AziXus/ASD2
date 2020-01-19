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

/**
 * 
 */
class Dictionary {
public:
    Dictionary(){
    }
    /**
     * Permet de générer les différents mots qui seront contenus dans le dictionnaire  
     * @param filename nom du fichier à partir duquel trouver les mots
     */
    void genererDico(std::string filename){
        std::string line;
        bool hasNoDigit = false;
        std::ifstream s(filename);
        while (std::getline(s, line)) {
            hasNoDigit = stringToLower(line);
            //Si un mot contient un digit pas d'ajout dans le dico
            if(hasNoDigit){
                std::chrono::high_resolution_clock::time_point debut = std::chrono::high_resolution_clock::now();
                insert(line);
                std::chrono::high_resolution_clock::duration temps = std::chrono::high_resolution_clock::now() - debut;
                creationTime += std::chrono::duration_cast<std::chrono::microseconds>(temps).count();
            }
        }
        s.close();
    }

    virtual void insert(const std::string& str)=0;

    virtual bool contains(const std::string& str)=0;
    
    long getCreation(){
        return creationTime;
    }
    
    long getSearch(){
        return searchTime;
    }
    
    protected:
        long creationTime = 0;
        long long searchTime = 0;
};

class DicoSTL : public Dictionary {
public:
    DicoSTL(const std::string& filename) {
        genererDico(filename);
    }

    void insert(const std::string& str) override {
        dico.insert(str);
    }

    bool contains(const std::string& str) override {
        std::chrono::high_resolution_clock::time_point debut = std::chrono::high_resolution_clock::now();
        bool b = dico.find(str) != dico.end();
        std::chrono::high_resolution_clock::duration temps = std::chrono::high_resolution_clock::now() - debut;
        this->searchTime += std::chrono::duration_cast<std::chrono::microseconds>(temps).count();
        return b;
    }

private:
    std::unordered_set<std::string> dico;
};

class DicoTST : public Dictionary {
public:
    DicoTST(std::string filename){
        genererDico(filename);
    }

    void insert(const std::string& str) override{
        dico.put(str);
    }

    bool contains(const std::string& str) override{
        std::chrono::high_resolution_clock::time_point debut = std::chrono::high_resolution_clock::now();
        bool b = dico.contains(str);
        std::chrono::high_resolution_clock::duration temps = std::chrono::high_resolution_clock::now() - debut;
        this->searchTime += std::chrono::duration_cast<std::chrono::microseconds>(temps).count();
        return b;
    }
    
private:
    TernarySearchTree dico;
};

#endif /* DICTIONARY_H */

