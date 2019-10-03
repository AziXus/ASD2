/* 
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 * Modified: Valentin Minder (2018), Raphaël Racine (2018), Antoine Rochat (2019)
 * Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 *
 * Created on 26. septembre 2014, 15:08
 * Description: Classe permettant de créer un graphe utilisant comme sommet des symboles
 */
#ifndef SYMBOLGRAPH_H
#define	SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph;
private:
    Graph* g;
    //Initialisation d'une structure map pour les symboles pour pouvoir stocker le numéro du sommet
    //correspondant au symbole
    std::unordered_map<std::string, int> symbole;
    //Initialisation d'un vecteur indexSymbole pour trouver rapidement un symbole en donnant l'index.
    std::vector<std::string> indexSymbole;
    typedef std::pair<int,int> Edge;

public:

    ~SymbolGraph()
    {
        delete g;
    }

    /**
     * création du SymbolGraph a partir du fichier movies.txt
     * @param filename string contenant le nom du fichier à lire
     */
    SymbolGraph(const std::string& filename) {
        //Création d'un vecteur d'arrête pour stocker les différentes arrêtes du graphe temporairement
        std::vector<Edge> edgeList;
        unsigned idxFilm = 0;//variable permettant de garder le numéro du dernier film ajouté au graphe
        unsigned idxActeur = 0;//variable permettant de garder le numéro du dernier acteur ajouté au graphe
        std::string line;
        std::ifstream s(filename);
        //Construction du graphe avec les strings
        while (std::getline(s, line))
        {
            auto names = split(line,'/');

            for(auto name : names ){
                //Si le symbole n'est pas encore contenu dans le graphe on l'ajoute sinon on ne lui ajoute que sa nouvelle arrête
                if(!contains(name)){
                    symbole.insert(std::pair<std::string, int>(name, idxActeur));
                    indexSymbole.push_back(name);
                    //Si l'index d'acteur est différent de celui film on ajoute une arête 
                    //sinon cela veut dire que c'est un film et donc pas d'arête à ajouter dans ce cas
                    if(idxActeur != idxFilm){
                         //Création de l'arête à ajouter entre film et acteur
                        edgeList.push_back(std::make_pair(idxFilm,idxActeur));
                    }
                    idxActeur++;
                }
                else{
                    //Recherche de l'index de l'acteur car il est déjà dans le graphe
                    edgeList.push_back(std::make_pair(idxFilm,index(name)));
                }
            }
            //On attribue à film la valeur d'acteur car un film est toujours en début de ligne
            idxFilm = idxActeur;
        }
        //Initialisation du graphe
        g = new GraphType(indexSymbole.size());
        //Boucle ajoutant toutes les arrêtes créées lors de la lecture du fichier dans le graphe
        for(Edge edge : edgeList ){
            g->addEdge(edge.first,edge.second);
        }

        s.close();
    }

    /**
     * Vérifie la présence d'un symbole
     * @param name string étant le symbole à trouver dans le graphe
     * @return si le symbole existe retourne true sinon false
     */
    bool contains(const std::string& name) const {
        return symbole.find(name) != symbole.end();
    }

    /**
     * Trouve l'index du sommet correspondant au symbole 
     * @param name string étant le symbole recherché
     * @return un entier étant l'index du symbole
     */
    int index(const std::string& name) const {
        return symbole.at(name);
    }

    /**
     * Trouve le symbole correspondant à l'index d'un sommet
     * @param idx entier étant l'index du sommet
     * @return string étant le symbole cherché
     */
    std::string symbol(int idx) const {
        return indexSymbole.at(idx);
    }

    /**
     * Trouve les symboles adjacents à un symbole
     * @param name string étant le symbole auquel il faut trouver les adjacents
     * @return une liste de string contenant les symboles adjacents
     */
    std::vector<std::string> adjacent(const std::string& name) const {
        std::vector<std::string> adj;
        for(int i : g->adjacent(index(name))){
            adj.push_back(symbol(i));
        }
        return adj;
    }

    const Graph& G() const {
        return *g;
    }

};


#endif	/* SYMBOLGRAPH_H */
