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
#include <map>

#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph;
private:
    Graph* g;
//    typedef std::pair<std::string, int> Vertex;
    std::vector<std::string> symboles;
    std::map<std::string, int> indices;
    // A IMPLEMENTER: vos structures privées ici.

public:

    ~SymbolGraph()
    {
        delete g;
    }

    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename) {
        /* A IMPLEMENTER */
        // Indication: nous autorisons une double lecture du fichier.

        // exemple de lecture du fichier, ligne par ligne puis element par element (separe par des /)
        int idx = 0;

        std::string line;

        std::ifstream s(filename);
        while (std::getline(s, line))
        {
            auto names = split(line,'/');

            for( auto name : names ) {
                if (name == "Bacon, Kevin") {
                    int wfds = 0;
                }
                if (!contains(name)) {
                    indices[name] = idx;
                    symboles.push_back(name);
                    ++idx;
                }
            }
        }

        //Retourne en début de fichier et clear eof flag
        s.clear();
        s.seekg(0, std::ios::beg);

        //Graphe de taille du nombre de symboles
        g = new Graph(symboles.size());

        //On ajoute les arêtes
        while (std::getline(s, line))
        {
            auto names = split(line,'/');

            int idxFilm = index(names[0]);
            for(size_t i = 1; i < names.size(); ++i) {
                g->addEdge(idxFilm, index(names[i]));
            }

        }

        s.close();
    }

    //verifie la presence d'un symbole
    bool contains(const std::string& name) const {
        /* A IMPLEMENTER */
        return indices.find(name) != indices.end();
    }

    //index du sommet correspondant au symbole
    int index(const std::string& name) const {
        /* A IMPLEMENTER */
        return indices.at(name);
    }

    //symbole correspondant au sommet
    std::string symbol(int idx) const {
        /* A IMPLEMENTER */
        return symboles.at(idx);
    }

    //indices adjacents a un symbole
    std::vector<std::string> adjacent(const std::string& name) const {
        /* A IMPLEMENTER */
        std::vector<std::string> adjacents;

        for(int w : g->adjacent(index(name))) {
            adjacents.push_back(symbol(w));
        }

        return adjacents;
    }

    const Graph& G() const {
        return *g;
    }

};


#endif	/* SYMBOLGRAPH_H */

