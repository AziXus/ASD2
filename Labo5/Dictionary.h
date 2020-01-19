/*
 * File:   Dictionnary.h
 * Author: Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 * Labo 6
 *
 * Description: Classe permettant l'implémentation des 2 strcutures de stockage et recherhce
 * de mots dans un dictionnaire
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
 * Classe Dictionnay implémentant les fonctions de base pour générer un dictionnaire 
 */
class Dictionary {
public:
    /**
     * Permet d'insérer les différents mots dans le dictionnaire  
     * @param filename nom du fichier à partir duquel trouver les mots
     */
    void genererDico(const std::string& filename){
        std::string line;
        bool hasNoDigit = false;
        std::ifstream s(filename);
        while (std::getline(s, line)) {
            hasNoDigit = stringToLower(line);
            //Si un mot contient un digit pas d'ajout dans le dictionnaire
            if(hasNoDigit){
                //Stockage d'un temps de départ
                std::chrono::high_resolution_clock::time_point debut = std::chrono::high_resolution_clock::now();
                insert(line);
                //Calcul du temps qu'a pris l'insertion
                std::chrono::high_resolution_clock::duration temps = std::chrono::high_resolution_clock::now() - debut;
                //Ajout du temps au temps total de toutes les dernières insertion(donnera le temps de création)
                creationTime += std::chrono::duration_cast<std::chrono::microseconds>(temps).count();
            }
        }
        s.close();
    }

    /**
     * Fonction abstraite permettant de définir une insertion dans un dictionnaire
     * @param str string constante étant le mot à insérer
     */
    virtual void insert(const std::string& str)=0;

    /**
     * Fonction abstraite permettant de définir l'appel à la fonction qui permet de définir 
     * si un mot est contenu dans un dictionnaire
     * @param str string constante étant le mot à trouver
     */
    virtual bool contains(const std::string& str)=0;
    
    /**
     * Fonction permettant de retourner la variable indiquant le temps de création du dictionnaire
     * @return un entier long étant le temps de création
     */
    long getCreation(){
        return creationTime;
    }
    
    /**
     * Fonction permttant de retourner la varibale indiquant le temps de recherche dans un dictionnaire
     * @return un entier long étant le temps de recherche
     */
    long getSearch(){
        return searchTime;
    }
    
    protected:
        long creationTime = 0;
        long long searchTime = 0;
};

/**
 * Classe DicoSTL héritant de la classe Dictionary
 * Nous utilisons cette classe pour implémenter la solution de stockage de dictionnaire avec
 * des structures de la STL.
 * Nous avons décidés d'utiliser une unordered_set pour stocker les différents mots
 * car cette structure utilise des fonctions de hachage pour socker les différents mots.
 * Comme vu en cours une table de hachage permet d'accèder à des éléments de manière linéaire dans le pire des cas
 * et en moyenne 3-5* et c'est pour cela que nous avons choisi cette strcuture.
 */
class DicoSTL : public Dictionary {
public:
    /**
     * Constructeur de la classe DicoSTL permet de générer le dictionnaire
     * @param filename string représentant le nom du fichier contenant le dictionnaire 
     */
    DicoSTL(const std::string& filename) {
        genererDico(filename);
    }

    /**
     * Fonction permettant d'insérer un mot dans le dictionnaire
     * @param str string étant le mot à insérer
     */
    void insert(const std::string& str) override {
        dico.insert(str);
    }

    /**
     * Fonction redéfinie permettant de vérifier si un mot est contenu dans le dictionnaire 
     * @param str string étant le mot recherché
     * @return vrai si le mot est trouvé, faux sinon
     */
    bool contains(const std::string& str) override {
        //Lance un temp de départ pour vérifier le temps total d'une recherche
        std::chrono::high_resolution_clock::time_point debut = std::chrono::high_resolution_clock::now();
        bool b = dico.find(str) != dico.end();
        //Calcul du temps de recherche
        std::chrono::high_resolution_clock::duration temps = std::chrono::high_resolution_clock::now() - debut;
        //Stockage du temps dans une variable allant contenir le temps total de toutes les recherches effectuées
        this->searchTime += std::chrono::duration_cast<std::chrono::microseconds>(temps).count();
        return b;
    }

private:
    //Stucture unordered_set représentant le dictionnaire
    std::unordered_set<std::string> dico;
};

/**
 * Classe permettant de générer un dictionnaire en utilisant l'implémenation d'un TST
 * @param filename
 */
class DicoTST : public Dictionary {
public:
    /**
     * Constructeur de la classe permet de générer un dictionnaire
     * @param filename string étant le nom du fichier depuis lequel générer le dictionnaire
     */
    DicoTST(const std::string& filename){
        genererDico(filename);
    }

    /**
     * Fonction redéfinie permettant d'insérer un mot dans le dictionnaire
     * @param str string étant le mot à insérer
     */
    void insert(const std::string& str) override{
        dico.put(str);
    }

    /**
     * Fonction redéfinie permettant de savoir si un mot est contenu dans le dictionnaire
     * @param str string étant le mot à trouver
     * @return vrai si le mot a été trouver, faux sinon
     */
    bool contains(const std::string& str) override{
        //Lance un temp de départ pour vérifier le temps total d'une recherche
        std::chrono::high_resolution_clock::time_point debut = std::chrono::high_resolution_clock::now();
        //Calcul du temps de recherche
        bool b = dico.contains(str);
        std::chrono::high_resolution_clock::duration temps = std::chrono::high_resolution_clock::now() - debut;        
        //Stockage du temps dans une variable allant contenir le temps total de toutes les recherches effectuées
        this->searchTime += std::chrono::duration_cast<std::chrono::microseconds>(temps).count();
        return b;
    }
    
private:
    TernarySearchTree dico;
};

#endif /* DICTIONARY_H */

