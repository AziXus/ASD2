/*
 * File:   TrainDiGraphWrapper.h
 * Author: Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 *
 * Last modified on 24 november 2019
 *
 * Wrapper encapsulant un TrainNetwork permettant d'appeller les
 * algorithmes de plus court chemin.
 */

#ifndef LABO3_TRAINDIGRAPHWRAPPER_H
#define LABO3_TRAINDIGRAPHWRAPPER_H


#include <functional>
#include "TrainNetwork.h"
#include "EdgeWeightedDigraph.h"

class TrainDiGraphWrapper {
private:
    const TrainNetwork* tn;
    const std::function<int(TrainNetwork::Line)> weightFunc;

public:
    //Utilise le même type d'edge qu'un EdgeWeightedDiGraph
    typedef typename EdgeWeightedDiGraph<int>::Edge Edge;

    /**
     * Constructeur de la classe TrainDiGraphWrapper
     * @param tn variable de type TrainNetwork étant le réseau ferroviaire pour lequel crée un graphe
     * @param func fonction permettant de mesurer le poids d'une arête.
     */
    TrainDiGraphWrapper(const TrainNetwork& tn, std::function<int(TrainNetwork::Line)> func) : tn(&tn), weightFunc(std::move(func)) {
    }

    /**
     * Renvoie la taille du graphe du réseau ferroviaire
     * @return un entier étant le nombre de sommet du graphe
     */
    int V() const {
        return (int)tn->cities.size();
    }

    /**
     * Permet d'appliquer une fonction sur chaque arrête du graphe
     * @param f la fonction a appliquée à toutes les arrêtes
     */
    template <typename Func>
    void forEachEdge(Func f) const {
        for (TrainNetwork::Line line : tn->lines) {
            int weight = weightFunc(line);
            Edge edge(line.cities.first, line.cities.second, weight);
            Edge edge2(line.cities.second, line.cities.first, weight);

            f(edge);
            f(edge2);
        }
    }

    /**
     * Permet d'appliquer une fonction sur chaque arrête adjacente du graphe
     * @param v entier répresentant le sommet auquel le parcours des ses adjacents est effectué
     * @param f la function a appliquée à toutes les arrêtes
     */
    template <typename Func>
    void forEachAdjacentEdge(int v, Func f) const {
        TrainNetwork::City city = tn->cities.at(v);

        for (int l : city.lines) {
            TrainNetwork::Line line = tn->lines.at(l);

            Edge edge(line.cities.first, line.cities.second, weightFunc(line));
            Edge edge2(line.cities.second, line.cities.first, weightFunc(line));

            f(edge);
            f(edge2);
        }
    }

};


#endif //LABO3_TRAINDIGRAPHWRAPPER_H
