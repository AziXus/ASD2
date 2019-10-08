/*
 * File:   DFSOrder.h
 * Author: Cuisenaire
 * Labo 2
 * Created on 3. novembre 2014, 08:23
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
    vector<string> files = {"prerequis.txt", "prerequis2.txt", "prerequis3.txt"};

    for (auto file : files) {
        try {
            SymbolGraph<DiGraph> SG(file, ',');
            TopologicalSort<DiGraph> TS(SG.G());

            cout << file << " est un DAG" << endl;

            cout << "Ordre topologique: " << endl;

            for (auto v : TS.Order()) {
                cout << SG.symbol(v) << " ";
            }

            cout << endl;

            if (checkOrder(TS.Order(), SG, file, ','))
                cout << "Vérification réussie" << endl;
            else
                cout << "Vérification échouée" << endl;
        } catch (exception& e) {
            cout << file << " n'est pas un DAG" << endl;
        }

        cout << "------------------------" << endl;
    }

    return EXIT_SUCCESS;
}
