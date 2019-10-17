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

    bool cycleTrouve = false;
    bool debutTrouve = false;
    int sommetDebutCycle;
    std::vector<bool> marque;
    std::vector<bool> stocke;
    
    void detectCycle(int v) {
        //Si v est dans le graphe

        marque[v] = true;
        stocke[v] = true;

        for (auto w : g->adjacent(v)) {
            //Si on a pas trouvé de cycle on continue la détection
            if(!cycleTrouve){
                if(!marque[w])
                    detectCycle(w);
                //Si le sommet est déjà stocké cela siginfie qu'on a un cycle
                else if(stocke[w]){
                    cycleTrouve = true;
                    //Ajout du sommets w car se sera le sommet de départ du cycle
                    cycleOrdre.push_back(w);
                    //Enregistrement du cycle w comme debut du cycle
                    sommetDebutCycle = w;
                }
            }
        }
        //Si un cycle est trouvé on ajoute les sommets v jusqu'à ce que le sommet de début de cycle soit trouvé
        //Quand se sera le cas cela voudra dire que le cycle est terminé
        if(cycleTrouve && !debutTrouve){
            cycleOrdre.push_back(v);
        }
        //Si le sommet étant le début du cycle est trouvé il ne faut plus ajouter de sommet la fin du cycle à été trouvée
        if(v == sommetDebutCycle)
            debutTrouve = true;
        stocke[v] = false;
    }

public:
    //constructeur
    DirectedCycle(const GraphType& g) {
        this->g = &g;

        marque.resize(this->g->V(), 0);
        stocke.resize(this->g->V(), 0);

        for (int v = 0; v < this->g->V(); ++v) {
            if(!marque[v]){
                detectCycle(v);
            }
        }
        //On inverse l'ordre de cycle car le graphe était inversé
        cycleOrdre.reverse();
    }

    //indique la presence d'un cycle
    bool HasCycle() {
        return cycleTrouve;
    }

    //liste les indexes des sommets formant une boucle
    std::list<int> Cycle() {
        return cycleOrdre;
    }
};

#endif
