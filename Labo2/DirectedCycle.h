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
    bool foundSommet = false;
    int debutCycle;
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
                    cycles.push_back(w);
                    debutCycle = w;
                }
	    }
            
            if(v == debutCycle)
                foundSommet=true;
            
            if(foundCycle && !foundSommet){
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
                    if(!marked[v])
                        detectCycle(v);
                
                    /*if (foundCycle)
                        cycles.push_back(v);*/

		    foundCycle = false;
//            std::fill(marked.begin(), marked.end(), false);
//            std::fill(stacked.begin(), stacked.end(), false);
		}
//                bool foundEndCycle = false;
//                int nbElementCycle = 0;
//                for(int v : cycles){
//                    for(auto w : sommets){
//                        if(v == w){
//                            foundEndCycle = true;
//                        }
//                    }
//                    nbElementCycle++;
//                }
//                for(int i = nbElementCycle; i < cycles.size();){
//                    cycles.erase(std::next(cycles.begin(), nbElementCycle + 1));
//                }
                //cycles.push_front(*(cycles.end()));
//                bool estCycle = false;
//                for(int v = 1; v < cycles.size(); ++v){
//                    for(int w : this->g->adjacent(*std::next(cycles.begin(),v))){
//                        if(w == *std::next(cycles.begin(),v))
//                            estCycle = true;
//                    }
//                    if(!estCycle){
//                        cycles.erase(std::next(cycles.begin(),v));
//                    }
//                    estCycle = false;
//                }
//                for(int v = 0; v < cycles.size(); ++v){
//                    if(!detectCycle(*std::next(cycles.begin(),v)))
//                        cycles.erase(std::next(cycles.begin(),v));
//                }
	}
	
	//indique la presence d'un cycle
	bool HasCycle() {
		/* A IMPLEMENTER */
		//return ...
		return cycles.size() != 0;
	}
	
	//liste les indexes des sommets formant une boucle
	std::list<int> Cycle() {
		/* A IMPLEMENTER */
		//return ...
		return cycles;
	}
	
};

#endif
