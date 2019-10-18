/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 * Modified: Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 * Labo 2
 * Created on 08. octobre 2014, 10:46
 *
 * Description: Classe permettant la detection de cycle sur un graphe oriente
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <list>
#include <vector>
#include <algorithm>


template<typename GraphType>
class DirectedCycle {
private:
    const GraphType* g;                         //Graphe sur lequel on recherche un cycle
    bool cycleTrouve = false;                   //Au moins un cycle trouvé
    bool cycleCompletRacine = false;            //Remonté le cycle jusqu'à sa racine
    int racineCycle;                            //Sommet duquel on commence et termine le cycle

    std::list<int> cycle;                       //Sommets du cycle
    std::vector<bool> marque;                   //Sommet visité ou non
    std::vector<bool> stocke;                   //Sommet dans la pile ou non

    /*
     * @brief   détecte la présence d'un cycle dans le graphe
     * @param   v l'index d'un sommet du graphe
     */
    void detectCycle(int v) {
        marque[v] = true;                       //On marque v comme visité
        stocke[v] = true;                       //Empilage de v

        for (auto w : g->adjacent(v)) {
            if(!cycleTrouve){
                if(!marque[w])
                    detectCycle(w);
                else if(stocke[w]){             //Si le sommet est déjà stocké cela signifie qu'on commence un cycle
                    cycleTrouve = true;
                    cycle.push_back(w);         //Ajout du sommet racine du cycle
                    racineCycle = w;            //Enregistrement du sommet comme racine du cycle
                }
            }
        }

        if(cycleTrouve && !cycleCompletRacine)  //Si un cycle a été trouvé on ajoute les sommets jusqu'à ce qu'on
            cycle.push_back(v);                 //remonte le cycle complet (jusqu'à la racine)
        if(v == racineCycle)                    //Si le sommet est le même qu'au début du cycle
            cycleCompletRacine = true;          //On a effectué le cycle complet

        stocke[v] = false;                      //Désempilage de v
    }

public:
    /*
     * @brief   constructeur, effectue directement la détection de cycle
     * @param   g le graphe sur lequel on recherche un cycle
     */
    DirectedCycle(const GraphType& g) {
        this->g = &g;
        marque.resize(this->g->V(), 0);
        stocke.resize(this->g->V(), 0);

        for (int v = 0; v < this->g->V(); ++v) { //On boucle s'il reste des sommets non visités
            if(!marque[v]){                      //(plusieurs composantes connexes)
                detectCycle(v);
            }
        }
        cycle.reverse();                         //On inverse l'ordre de cycle car le graphe était inversé
    }

    /*
     * @brief   indique la presence d'au moins un cycle
     * @return  true si au moins un cycle a été trouvé, sinon false
     */
    bool HasCycle() {
        return cycleTrouve;
    }

    /*
     * @brief   liste les indexes des sommets formant un cycle
     * @return  les sommets formant un cycle sous forme d'une liste d'indexes
     */
    std::list<int> Cycle() {
        return cycle;
    }
};

#endif
