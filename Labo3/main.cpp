//
//  main.cpp
//  Labo3
//
//  Created by Olivier Cuisenaire on 18.11.14.
//
//

#include <cstdlib>
#include <iostream>
#include <ctime>

#include "TrainNetwork.h"
#include "MinimumSpanningTree.h"
#include "ShortestPath.h"
#include "TrainGraphWrapper.h"

#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDiGraph.h"

#include "TrainGraphWrapper.h"
#include "TrainDiGraphWrapper.h"

using namespace std;
//TODO retourne -1 si pas trouvé
int getIndex(const string& cityName, const TrainNetwork& tn){
    for(size_t i = 0; i < tn.cities.size(); ++i){
        if(cityName == tn.cities.at(i).name){
            return i;
        }
    }
    return -1;
}

string getCityName(size_t index, const TrainNetwork& tn){
    return tn.cities[index].name;
}

void afficheChemin(const string& path, int total, bool evalByDist){
    if(evalByDist){
        cout << "longueur = " << total << " km" << endl;
    }else{
        cout << "temps = " << total << " minutes" << endl;
    }
    cout << "via " << path << endl;
}


int plusCourtCheminCommon(const string& depart, const string& arrivee, string& path, TrainNetwork& tn, const std::function<int(TrainNetwork::Line)> &f){
    TrainDiGraphWrapper tgw = TrainDiGraphWrapper(tn, f);
    int departIndex = getIndex(depart, tn); //TODO gérer pas trouvé
    int arriveeIndex = getIndex(arrivee, tn);
    auto shortestPath = DijkstraSP<TrainDiGraphWrapper>(tgw, departIndex);
    auto pathTo = shortestPath.PathTo(arriveeIndex);
    int total= 0;

    for(auto edge : pathTo){
        path += getCityName(edge.From(), tn) + " -> ";
        total += edge.Weight();
    }
    return total;
}


// Calcule et affiche le plus court chemin de la ville depart a la ville arrivee
// en passant par le reseau ferroviaire tn. Le critere a optimiser est la distance.
void PlusCourtChemin(const string& depart, const string& arrivee, TrainNetwork& tn) {
    string path;
    int total = plusCourtCheminCommon(depart, arrivee, path, tn, [](TrainNetwork::Line l){ return l.length; });
    path += arrivee;
    afficheChemin(path, total, true);
}



// Calcule et affiche le plus court chemin de la ville depart a la ville arrivee
// en passant par le reseau ferroviaire tn ayant une ville en travaux et donc
// inaccessible. Vous pouvez mettre un cout infini aux arcs ayant comme depart ou
// comme arrivee cette ville en travaux. Le critere a optimiser est la distance.
void PlusCourtCheminAvecTravaux(const string& depart, const string& arrivee, const string& gareEnTravaux, TrainNetwork& tn) {
    int travauxIndex = getIndex(gareEnTravaux, tn);

    string path;
    int total = plusCourtCheminCommon(depart, arrivee, path, tn, [travauxIndex](TrainNetwork::Line l){
        if(l.cities.first == travauxIndex || l.cities.second == travauxIndex) return std::numeric_limits<int>::max();
        return l.length;
    });
    path += arrivee;
    afficheChemin(path, total, true);
}

// Calcule et affiche le plus rapide chemin de la ville depart a la ville arrivee via la ville "via"
// en passant par le reseau ferroviaire tn. Le critere a optimiser est le temps de parcours
void PlusRapideChemin(const string& depart, const string& arrivee, const string& via, TrainNetwork& tn) {   //TODO factorize
    string path;
    int total = plusCourtCheminCommon(depart, via, path, tn, [](TrainNetwork::Line l){ return l.duration; });
    total += plusCourtCheminCommon(via, arrivee, path, tn, [](TrainNetwork::Line l){ return l.duration; });
    path += arrivee;

    afficheChemin(path, total, false);
}


// Calcule et affiche le plus reseau a renover couvrant toutes les villes le moins cher.
// Le prix pour renover 1 km de chemin de fer est de :
// - 15 CHF par km pour les lignes ayant 4 voies
// - 10 CHF par km pour les lignes ayant 3 voies
// - 6 CHF par km pour les lignes ayant 2 voies
// - 3 CHF par km pour les lignes ayant 1 voie
void ReseauLeMoinsCher(TrainNetwork &tn) {
    const int prixPourNbVoies[] = {3,6,10,15};
    TrainGraphWrapper tgw = TrainGraphWrapper(tn, [&prixPourNbVoies] (TrainNetwork::Line l){
        return l.length*prixPourNbVoies[l.nbTracks -1];
    });
    auto mst = MinimumSpanningTree<TrainGraphWrapper>::EagerPrim(tgw);  //Arbre recouvrant de poids minimum
    int cost = 0;

    for(auto edge : mst){
        cout << getCityName(edge.Either(), tn) << " - " << getCityName(edge.Other(edge.Either()), tn) << " : " << edge.Weight() << " MF" << endl;
        cost += edge.Weight();
    }
    cout << "Cout total : " << cost << " MF" << endl;
}

// compare les algorithmes Dijkstra et BellmanFord pour calculer les plus courts chemins au
// sommet 0 dans le graphe defini par filename.
void testShortestPath(string filename)
{
    cout << "Testing " << filename << endl;
    
    bool ok = true;
    
    typedef EdgeWeightedDiGraph<double> Graph;
    Graph ewd(filename);
    
    clock_t startTime = clock();
    
    BellmanFordSP<Graph> referenceSP(ewd,0);
    
    cout << "Bellman-Ford: " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    startTime = clock();
    
    DijkstraSP<Graph> testSP(ewd,0);
    
    cout << "Dijkstra:     " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    
    for (int v=0; v<ewd.V(); ++v) {
        if (referenceSP.DistanceTo(v) != testSP.DistanceTo(v) ) {
            cout << "Oops: vertex" << v << " has " << referenceSP.DistanceTo(v) << " != " <<  testSP.DistanceTo(v) << endl;
            ok = false;
            break;
        }
    }
    
    if(ok) cout << " ... test succeeded " << endl << endl;
}



int main(int argc, const char * argv[]) {   //TODO supprimer exemples commentés

    testShortestPath("tinyEWD.txt");
    testShortestPath("mediumEWD.txt");
    testShortestPath("1000EWD.txt");
    //testShortestPath("10000EWD.txt");
    
    TrainNetwork tn("reseau.txt");
    
    cout << "1. Chemin le plus court entre Geneve et Coire" << endl;
    
   // PlusCourtChemin("Geneve", "Coire", tn);
    PlusCourtChemin("Lausanne", "Berne", tn);
    
    cout << "2. Chemin le plus court entre Geneve et Coire, avec la gare de Sion en travaux" << endl;
    
   // PlusCourtCheminAvecTravaux("Geneve", "Coire", "Sion", tn);
    PlusCourtCheminAvecTravaux("Lausanne", "Berne", "Romont", tn);

    cout << "3. Chemin le plus rapide entre Geneve et Coire en passant par Brigue" << endl;
    
    //PlusRapideChemin("Geneve", "Coire", "Brigue", tn);
    PlusRapideChemin("Lausanne", "Berne", "Viege", tn);
    
    cout << "4. Chemin le plus rapide entre Lausanne et Zurich en passant par Bale" << endl;
    
    PlusRapideChemin("Lausanne", "Zurich", "Bale", tn);
    
    cout << "5. Quelles lignes doivent etre renovees ? Quel sera le cout de la renovation de ces lignes ?" << endl;
    
    ReseauLeMoinsCher(tn);
    
    return 0;
}

