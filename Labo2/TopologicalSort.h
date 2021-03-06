/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 * Modified: Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 * Labo 2
 * Created on 08. octobre 2014, 14:07
 *
 * Description: Classe permettant le tri topologique d'un graphe oriente.
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include "ParcoursEnProfondeur.h"
#include <list>
#include <vector>
#include <exception>
#include <algorithm>

template < typename GraphType >
class TopologicalSort {
private:
	std::vector<int> topologie;

public:
    /**
     * Constructeur spécifique de la classe TopologicalSort
     * @param g grapheType étant le graphe auquel effectué un tri topologique
     * @throws GraphNotDAGException si le graphe contient un cycle
     */
    TopologicalSort(const GraphType & g) {
        //Création d'un graphe directedCycle pour vérifier s'il contient un cycle
        DirectedCycle<GraphType> dc(g);

        //En cas de cycle, on lève une exception GraphNotDAGException avec le cycle en paramètre
        if (dc.HasCycle())
            throw GraphNotDAGException(dc.Cycle());

        DFS<GraphType> dfs(g);

        //Effectue le parcours dfs de tout le graphe et ajoute les sommets au vecteur topologie
        //en post-ordre
        dfs.visitGraph([] (int){}, [this](int v) { this->topologie.push_back(v); });

        //Inverse le vecteur pour obtenir le bon ordre
	std::reverse(topologie.begin(), topologie.end());
    }
    
    //tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
    const std::vector<int>& Order() {
        return topologie;
    }
    
    //exception si le graphe n'est pas un DAG (Directed Acyclic Graph)
    class GraphNotDAGException : public std::exception {
        
    private:
        //indexes des sommets du cycle qui empeche le tris topologique
        const std::list<int> cycle;
        
    public:
        GraphNotDAGException(const std::list<int> cycle) noexcept : exception(), cycle(cycle) {
            
        }
        
        virtual const char* what() const noexcept {
            return "Topological sort impossible : the graph is not a DAG";
        }
        
        const std::list<int>& Cycle() const noexcept {
            return cycle;
        }
    };
};


#endif
