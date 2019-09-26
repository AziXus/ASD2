/* 
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 * Modified: Valentin Minder (2018), Raphaël Racine (2018), Antoine Rochat (2019)
 * Müller Robin, , Teixeira Carvalho Stéphane
 *
 * Created on 26. septembre 2014, 15:08
 * Description: Classe permettant de de créer un graphe utilisant comme sommet des symboles
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

#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph;
private:
    Graph* g;
    //Initialisation d'une structure map pour les symboles pour pouvoir stocker le numéro du sommet
    //correspondant au symbole
    std::map<std::string, int> symbole;
    //Initialisation d'un vecteur indexSymbole pour trouver rapidement l'index d'un symbole.
    std::vector<std::string> indexSymbole;
    typedef std::pair<int,int> Edge;

public:

    ~SymbolGraph()
    {
        delete g;
    }

    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename) {
        //Création d'un vecteur d'arrête pour stocker les différentes arrêtes du graphe temporairement
        std::vector<Edge> edgeList;
        unsigned film = 0;//variable permettant de garder le numéro du dernier film ajouté au graphe
        unsigned acteur = 0;//variable permettant de garder le numéro du dernier acteur ajouté au graphe
        std::string line;
        //Construction du graphe avec les strings
        std::ifstream s(filename);
        while (std::getline(s, line))
        {
            auto names = split(line,'/');

            for(auto name : names ){
                //Si le symbole n'est pas encore contenu dans le graphe on l'ajoute sinon on ne lui ajoute que sa nouvelle arrête
                if(!contains(name)){
                    symbole.insert(std::pair<std::string, int>(name, acteur));
                    indexSymbole.push_back(name);
                    //Création de l'arête à ajouter entre film et acteur
                    edgeList.push_back(std::make_pair(film,acteur));
                    acteur++;
                }
                else{
                    //enregistrement de la valeur de l'acteur actuel pour ne pas recommencer le comptage
                    size_t temp = acteur;
                    //Recherche de l'index de l'acteur car il est déjà dans le graphe
                    acteur = index(name);
                    edgeList.push_back(std::make_pair(film,acteur));
                    acteur = temp;
                }
            }
            //On attribue à film la valeur acteur car le nom du film commence toujours une ligne
            film = acteur;
        }
        //Initialisation du graphe
        g = new GraphType(indexSymbole.size());
        //Boucle ajoutant toutes les arrêtes créées lors de la lecture du fichier dans le graphe
        for(Edge edge : edgeList ){
            g->addEdge(edge.first,edge.second);
        }

        s.close();
    }

    //verifie la presence d'un symbole
    bool contains(const std::string& name) const {
        return symbole.find(name) != symbole.end();
    }

    //index du sommet correspondant au symbole
    int index(const std::string& name) const {
        return symbole.at(name);
    }

    //symbole correspondant au sommet
    std::string symbol(int idx) const {
        return indexSymbole.at(idx);
    }

    //symboles adjacents a un symbole
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
