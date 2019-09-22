/* 
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 * Modified: Valentin Minder (2018), Raphaël Racine (2018), Antoine Rochat (2019)
 *
 * Created on 26. septembre 2014, 15:08
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
    std::map<std::string, int> symbole;
    std::vector<std::string> indexSymbole;
    typedef std::pair<int,int> Edge;
    std::vector<Edge> edgeList;
    // A IMPLEMENTER: vos structures privées ici.

public:

    ~SymbolGraph()
    {
        delete g;
    }

    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename) {
        //Graph SymbolGraph;

        /* A IMPLEMENTER */
        // Indication: nous autorisons une double lecture du fichier.
        unsigned film = 0;
        unsigned acteur = 0;
        std::string line;
        //Construction du graphe avec les strings
        std::ifstream s(filename);
        while (std::getline(s, line))
        {
            auto names = split(line,'/');

            for(auto name : names ) {
                if(!contains(name)){
                    symbole.insert(std::pair<std::string, int>(name, acteur));
                    indexSymbole.push_back(name);
                    edgeList.push_back(std::make_pair(film,acteur));
                    acteur++;
                }
                else{
                    size_t temp = acteur;
                    acteur = index(name);
                    edgeList.push_back(std::make_pair(film,acteur));
                    acteur = temp;
                }
            }
            film = acteur;
        }

        g = new GraphType(edgeList.size()*2);

        for(Edge edge : edgeList ){
            g->addEdge(edge.first,edge.second);
        }
        // exemple de lecture du fichier, ligne par ligne puis element par element (separe par des /)
        //Construction du graphe avec les num

        s.close();
        //g = &SymbolGraph;
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
