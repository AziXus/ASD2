/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 * Created on 08. octobre 2014, 10:46
 *
 * A implementer
 * Classe permettant la detection de cycle sur un graphe oriente
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <list>
#include <vector>
#include <algorithm>


template<typename GraphType>
class DirectedCycle {
private:
    /* A DEFINIR */
    const GraphType* g;
    std::vector<int> cycles;
    std::list<int> cycleOrdre;

    bool foundCycle = false;
    bool foundRoot = false;
    int rootCycle;
    std::vector<bool> marked;
    std::vector<bool> stacked;

    void detectCycle(int v) {
        //Si v est dans le graphe

        marked[v] = true;
        stacked[v] = true;

        for (auto w : g->adjacent(v)) {
            //Si on a trouvé un cycle on fait rien et on continue l'exécution de la fonction
            if(foundCycle){
            }
            else if(!marked[w])
                detectCycle(w);
            else if(stacked[w]){
                foundCycle = true;
                cycleOrdre.push_back(w);
                //Ajoute les sommets formant le cycle car stacked contient les sommets visité jusqu'à la détection du cycle
                //On ajoute les sommets contenu dans le cycle dans l'ordre décroissant de leur index(Le graphe est inversé)
                for(int i = 0; i < stacked.size(); i++)
                    if(stacked[i]){
                        cycles.push_back(i);
                    }
            }
        }
        //En remontant on va ajouter dans cycleOrdre les sommets dans l'ordre de parcours du cycle
        //On connaît l'ordre du parcours des sommets grâce à la fonction de récursion detectCycle
        for(int i = 0; i < cycles.size(); i++)
            if(v == cycles[i])
                cycleOrdre.push_back(v);
        stacked[v] = false;
    }

public:
    //constructeur
    DirectedCycle(const GraphType& g) {
        /* A IMPLEMENTER */
        this->g = &g;

        marked.resize(this->g->V(), 0);
        stacked.resize(this->g->V(), 0);

        for (int v = 0; v < this->g->V(); ++v) {
            if(!marked[v]){
                detectCycle(v);
            }
        }
        cycleOrdre.reverse();
    }

    //indique la presence d'un cycle
    bool HasCycle() {
        return foundCycle;
    }

    //liste les indexes des sommets formant une boucle
    std::list<int> Cycle() {
        return cycleOrdre;
    }
};

#endif
