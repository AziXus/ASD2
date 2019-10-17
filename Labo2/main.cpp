/*
 * File:   main.cpp
 * Author: Cuisenaire
 * Modified: Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 * Labo 2
 * Created on 3. novembre 2014, 08:23
 * Description: Programme effectuant un tri topologique sur un graphe et si celui-ci contient un cycle
 * il arrête le tri et renvoie les sommets formant le cycle
 */


#include <cstdlib>
#include <iostream>
#include "Util.h"
#include "DiGraph.h"
#include "SymbolGraph.h"
#include "TopologicalSort.h"

using namespace std;

//methode permettant de verifier le graphe trie par rapport au fichier d'entree
bool checkOrder(const std::vector<int>& order,
                const SymbolGraph<DiGraph>& SG,
                const std::string& filename,
                char delim) {

    std::vector<int> positionInOrder(order.size());
    for( size_t i = 0; i < order.size(); ++i )
        positionInOrder[order[i]] = int(i);
    
    bool ok = true;
    
    std::string line;
    
    std::ifstream s(filename);
    while (std::getline(s, line))
    {
        auto names = split(line,delim);
        
        for(size_t i = 1; i < names.size(); ++i) {
         
            int v = SG.index(names[0]); // module
            int w = SG.index(names[i]); // ieme prerequis
            
            if ( positionInOrder[ v ] < positionInOrder [ w ]) {
                cout << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
                ok = false;
            } 
        }
    }
    s.close();
    
    return ok;
}

int main(int argc, const char * argv[]) {
    //Déclaration des deux fichiers contenant les valeurs des graphes à générer
    string file("prerequis.txt");
    string file2("prerequis2.txt");
    //Création du graphe contenant les symboles
    SymbolGraph<DiGraph> SG(file2, ',');
    try{
        //On effectue le tri topologique sur le graphe des sommets
        //On inverse le graphe pour pouvoir avoir les dépendences des différents module correctes
        TopologicalSort<DiGraph> t(SG.G().reverse());
        cout << file << " est un DAG"  << endl;
        cout << "Ordre topologique : " << endl;
        //Affichage de l'ordre topologique
        for(int i = 0; i < SG.G().V(); i++){
            cout << SG.symbol(t.Order()[i]) << " ";
        }
        cout << endl;
        cout << (checkOrder(t.Order(), SG, file, ',') ? "Verification reussie" : "Verification erronee") << endl;

    }catch(TopologicalSort<DiGraph>::GraphNotDAGException& e){
        //Si une exception est attrapée cela veut dire que le graphe contient un cycle 
        //et donc que le tri ne peut pas être appliqué
        DirectedCycle<DiGraph> t(SG.G().reverse());
        cout << file2 << " n'est un DAG"  << endl;
        cout << "Cycle trouve" << endl;
        for(int i : t.Cycle())
            cout << SG.symbol(i) << " ";
        cout << endl;
        //Affichage du cycle trouvé dans le graphe
        for(int i : e.Cycle())
            cout << SG.symbol(i) << " ";
    }
    return EXIT_SUCCESS;
}
