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


template<typename GraphType>
class DirectedCycle {
private:
    /* A DEFINIR */
    const GraphType* g;
    std::list<int> cycles;

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
            if(foundCycle){
                return;
            }
            else if(!marked[w])
                detectCycle(w);
            else if(stacked[w]){
                foundCycle = true;
                rootCycle = w;
                cycles.push_back(w);
            }
        }
        if(v == rootCycle){
            foundRoot = true;
            cycles.push_back(v);
        }
        if(foundCycle && !foundRoot){
            cycles.push_back(v);
        }
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
            foundCycle = false;
        }
    }

    //indique la presence d'un cycle
    bool HasCycle() {
        return cycles.size() != 0;  //TODO return foundCycle -> pb
    }

    //liste les indexes des sommets formant une boucle
    std::list<int> Cycle() {
        return cycles;
    }

};

#endif
