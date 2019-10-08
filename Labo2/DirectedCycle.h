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

template<typename GraphType>
class DirectedCycle {
private:
	/* A DEFINIR */
	const GraphType* g;
    std::list<int> cycles;

	bool foundCycle = false;
    std::vector<bool> marked;
    std::vector<bool> stacked;

	void detectCycle(int v) {
	    //Si v est dans le graphe

	    marked[v] = true;
	    stacked[v] = true;

	    for (auto w : g->adjacent(v)) {
	        if (foundCycle)
	            return;
	        else if (!marked[w])
	            detectCycle(w);
	        else if (stacked[w])
	            foundCycle = true;
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

		    if (foundCycle)
                cycles.push_back(v);

//		    foundCycle = false;
//            std::fill(marked.begin(), marked.end(), false);
//            std::fill(stacked.begin(), stacked.end(), false);
		}
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
