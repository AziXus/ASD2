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

class TrainGraphWrapper{
private:
    const TrainNetwork* tn;
    const std::function<int(TrainNetwork::Line)> weightFunc;
    
public:  
    //Définition du type des arrête(Edge) ici elles seront de type WeightedEdge
    typedef WeightedEdge<int> Edge;
    /**
     * Constructeur de la classe TrainGraphWrapper
     * @param tn variable de type TrainNetwork étant le réseau ferroviaire pour lequel crée un graphe
     */
    TrainGraphWrapper(const TrainNetwork& i, std::function<int(TrainNetwork::Line)> weigthFunc) : tn(&i), weightFunc(std::move(weigthFunc)) {}
    /**
     * Renvoie la taille du graphe du réseau ferroviaire
     * @return un entier étant le nombre de sommet du graphe
     */
    int V() const{ 
        return (int)tn->cities.size();
    }
    /**
     * Permet d'appliquer une fonction sur chaque arrête du graphe
     * @param f la fonction a appliquée à toutes les arrêtes
     */
    template <typename Func>
    void forEachEdge(Func f) const{
        for(TrainNetwork::Line l : tn->lines){
            int weight = weightFunc(l);
            Edge edge(l.cities.first, l.cities.second, weight);
            f(edge);
        }
    }
    /**
     * Permet d'appliquer une fonction sur chaque arrête adjacente du graphe 
     * @param v entier répresentant le sommet auquel le parcours des ses adjacents est effectué
     * @param f la function a appliquée à toutes les arrêtes 
     */
    template <typename Func>
    void forEachAdjacentEdge(int v, Func f) const{
        int weight = 0;       
        for(int i : tn->cities.at(v).lines){
            TrainNetwork::Line l = tn->lines.at(i);
            weight = weightFunc(l);
            Edge edge(l.cities.first, l.cities.second, weight);
            f(edge);
        }
    }
};

#endif	/* DIGRAPH_H */
