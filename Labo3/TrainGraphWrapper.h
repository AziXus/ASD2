/* 
 * File:   DiGraph.h
 * Author: Cuisenaire
 *
 * Created on 7. octobre 2014, 16:54
 * 
 * Implementation d'un graphe oriente par liste d'adjacence
 */

#ifndef TRAINGRAPHWRAPPER_H
#define	TRAINGRAPHWRAPPER

#include "TrainNetwork.h"
#include "EdgeWeightedGraphCommon.h"
#include "EdgeWeightedGraph.h"

class TrainGraphWrapper {
private:
    const TrainNetwork* tn;
    EdgeWeightedGraph<int> edgeGraph;
    
public:  
    //Définition du type des arrête(Edge) ici elles seront de type WeightedEdge
    typedef WeightedEdge<int> Edge;
    /**
     * Contructeur de la classe TrainGraphWrapper
     * @param tn variable de type TrainNetwork étant le réseau ferroviaire pour lequel crée un graphe
     */
    TrainGraphWrapper(const TrainNetwork& i) : tn(&i), edgeGraph(i.lines.size()) {
        //Ajout des arêtes dans edgeGraph
        for(unsigned i = 0; i < tn->lines.size(); i++){
            //A améliorer de ouf
            switch(tn->lines.at(i).nbTracks){
                case 1 : edgeGraph.addEdge(tn->lines.at(i).cities.first, tn->lines.at(i).cities.second, tn->lines.at(i).length * 3);
                break;
                case 2 : edgeGraph.addEdge(tn->lines.at(i).cities.first, tn->lines.at(i).cities.second, tn->lines.at(i).length * 6);
                break;
                case 3 : edgeGraph.addEdge(tn->lines.at(i).cities.first, tn->lines.at(i).cities.second, tn->lines.at(i).length * 10);
                break;
                case 4 : edgeGraph.addEdge(tn->lines.at(i).cities.first, tn->lines.at(i).cities.second, tn->lines.at(i).length * 15);
                break;
                default: std::cout << "inconnu";
                break;
            }
        }
    }
    /**
     * Renvoie la taille du graphe du réseau ferroviaire
     * @return un entier étant le nombre de sommet du graphe
     */
    int V() const{ 
        return tn->cities.size(); 
    }
    /**
     * Permet d'appliquer une fonction sur chaque arrête du graphe
     * @param f la function a appliquée à toutes les arrêtes 
     */
    template <typename Func>
    void forEachEdge(Func f) const{
        edgeGraph.forEachEdge(f);
    }
    /**
     * Permet d'appliquer une fonction sur chaque arrête adjacente du graphe 
     * @param v entier répresentant le sommet auquel le parcours des ses adjacents est effectué
     * @param f la function a appliquée à toutes les arrêtes 
     */
    template <typename Func>
    void forEachAdjacentEdge(int v, Func f) const{
        edgeGraph.forEachAdjacentEdge(v, f);
    }
};

#endif	/* DIGRAPH_H */
