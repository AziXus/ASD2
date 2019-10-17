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
    const GraphType* g;
    //Contient les sommets formant un cycle dans l'ordre décroissant de leur index
    std::vector<int> cycle;
    //Contient le cycle dans l'ordre de parcours des sommets
    std::list<int> cycleOrdre;

    bool foundCycle = false;
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
                //Ajout du sommets w car se sera le sommet de départ du cycle
                cycleOrdre.push_back(w);
                //Ajout des sommets formant le cycle car stacked contient les sommets visité jusqu'à la détection du cycle
                //Les sommets seront rajoutés dans le vecteur contenant le cycle dans l'ordre décroissant de leur index(Le graphe est inversé)
                for(int i = 0; i < stacked.size(); i++)
                    if(stacked[i]){
                        cycle.push_back(i);
                    }
            }
        }
        //Ajout dans cycleOrdre des sommets dans l'ordre de parcours du graphe
        //L'ordre du parcours des sommets est connu grâce à la récursion
        for(int i = 0; i < cycle.size(); i++)
            if(v == cycle[i])
                cycleOrdre.push_back(v);
        stacked[v] = false;
    }

public:
    //constructeur
    DirectedCycle(const GraphType& g) {
        this->g = &g;

        marked.resize(this->g->V(), 0);
        stacked.resize(this->g->V(), 0);

        for (int v = 0; v < this->g->V(); ++v) {
            if(!marked[v]){
                detectCycle(v);
            }
        }
        //On inverse l'ordre de cycle car le graphe était inversé
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
