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
            //Si on a trouvé un cycle on fait rien et on continue l'exécution de la fonction
            if(cycleTrouve){
            }
            else if(!marque[w])
                detectCycle(w);
            //Si le sommet est déjà stocké cela siginfie qu'on a un cycle
            else if(stocke[w]){
                cycleTrouve = true;
                //Ajout du sommets w car se sera le sommet de départ du cycle
                cycleOrdre.push_back(w);
                //Enregistrement du cycle w comme debut du cycle
                sommetDebutCycle = w;
                //Ajout des sommets formant le cycle car stacked contient les sommets visité jusqu'à la détection du cycle
                //Les sommets seront rajoutés dans le vecteur contenant le cycle dans l'ordre décroissant de leur index(Le graphe est inversé)
//                for(int i = 0; i < stocke.size(); i++)
//                    if(stocke[i]){
//                        cycle.push_back(i);
//                    }
            }
        }
        //Si un cycle est trouvé on ajoute les sommets v jusqu'à ce que on retombe sur le sommet de début de cycle
        if(cycleTrouve && !debutTrouve){
            cycleOrdre.push_back(v);
        }
        //Si on trouve le sommet étant le début du cycle il ne faut plus ajouter de sommet
        if(v == sommetDebutCycle)
            debutTrouve = true;
        //Ajout dans cycleOrdre des sommets dans l'ordre de parcours du graphe
        //L'ordre du parcours des sommets est connu grâce à la récursion
//        for(int i = 0; i < cycle.size(); i++)
//            if(v == cycle[i])
//                cycleOrdre.push_back(v);
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
