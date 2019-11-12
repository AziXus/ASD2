
#ifndef LABO3_TRAINDIGRAPHWRAPPER_H
#define LABO3_TRAINDIGRAPHWRAPPER_H


#include <functional>
#include "TrainNetwork.h"
#include "EdgeWeightedDigraph.h"

// Type du graphe pondere oriente a traiter
// GraphType doit se comporter comme un
// EdgeWeightedDiGraph et definir forEachEdge(Func),
// ainsi que le type GraphType::Edge. Ce dernier doit
// se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
// To() et Weight()

// Type du graphe pondere oriente a traiter
// GraphType doit se comporter comme un
// EdgeWeightedDiGraph et definir le
// type GraphType::Edge

// Comportement : EdgeWeightedDiGraph
// Types : GraphType::Edge (comportement DirectedEdge)

class TrainDiGraphWrapper {
private:
    const TrainNetwork* tn;
    const std::function<int(TrainNetwork::Line)> weightFunc;

public:
    typedef typename EdgeWeightedDiGraph<int>::Edge Edge;

    TrainDiGraphWrapper(const TrainNetwork* tn, std::function<int(TrainNetwork::Line)> func) : tn(tn), weightFunc(func) {

    }

    int V() const {
        return (int)tn->cities.size();
    }

    // From : EdgeWeightedGraphCommon
    // Parcours de tous les arcs du graphe.
    // la fonction f doit prendre un seul argument de type
    // EdgeWeightedDiGraph::Edge
    // Fonctions edges : From(), To() et Weight()
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

    // From : EdgeWeightedGraphCommon
    // Parcours des arcs/arêtes adjacentes au sommet v.
    // la fonction f doit prendre un seul argument de type
    // EdgeWeightedGraphCommon::Edge
    template <typename Func>
    void forEachAdjacentEdge(int v, Func f) const {

        TrainNetwork::City city = tn->cities.at(v);

        for (int l : city.lines) {
            TrainNetwork::Line line = tn->lines.at(l);

            int weight = weightFunc(line);
            Edge edge(line.cities.first, line.cities.second, weight);
            Edge edge2(line.cities.second, line.cities.first, weight);

            f(edge);
            f(edge2);
        }
    }

};


#endif //LABO3_TRAINDIGRAPHWRAPPER_H
