/*
 -----------------------------------------------------------------------------------
 Laboratoire : <nn>
 Fichier     : TernarySearchTree.cpp
 Auteur(s)   : Robin Müller
 Date        : 10.01.2020

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#ifndef LABO5_TERNARYSEARCHTREE_H
#define LABO5_TERNARYSEARCHTREE_H

#include <string>

class TernarySearchTree {
private:

    //
    // Noeud de l'arbre. contient une cle, une valeur, et les liens vers les
    // sous-arbres droit, gauche et du millieu.
    //
    struct Node {
    public:
        char c;
        bool end;
        Node* right; // sous arbre avec des cles plus grandes
        Node* center;
        Node* left;  // sous arbre avec des cles plus petites
//        int nodeSize; // taille du sous-arbre dont ce noeud est la racine.
        int nodeHeight; // hauteur du sous-arbre dont ce noeud est la racine.
        Node(char c, bool val) : c(c), end(val), right(nullptr), center(nullptr), left(nullptr),
                                 nodeHeight(0) {}
//                                 nodeSize(1), nodeHeight(0) {}
    };

    //
    // Racine de l'arbre.
    //
    Node* root;
public:
    size_t nbElements = 0;
private:

//    // HELPER: Mise à jour de la taille d'un sous-arbre à partir des taille de ses enfants
//    void updateNodeSize(Node* x) {
//        x->nodeSize = size(x->right) + size(x->left) + 1;
////        x->nodeSize = size(x->right) + size(x->center) + size(x->left) + 1;
//    }
    // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
    void updateNodeHeight(Node* x) {
        x->nodeHeight = std::max(height(x->right),height(x->left)) + 1;
    }

private:
    //
    // AVL: rotation droite avec mise à jour des tailles et hauteurs
    //
    Node* rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;

//        y->nodeSize = x->nodeSize;
//        updateNodeSize(x);

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }

    //
    // AVL: rotation gauche avec mise à jour des tailles et hauteurs
    //
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;

//        y->nodeSize = x->nodeSize;
//        updateNodeSize(x);

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }

    //
    // Constructeur. La racine est vide
    //
public:
    TernarySearchTree() : root(nullptr) { }

    //
    // Destructeur.
    //
public:
    ~TernarySearchTree() {
        deleteSubTree(root);
    }

private:
    void deleteSubTree(Node* x) {
        if( x == nullptr) return;
        deleteSubTree( x->right );
        deleteSubTree( x->center );
        deleteSubTree( x->left );
        delete x;
    }

//    //
//    // Nombre d'elements
//    //
//public:
//    int size() {
//        return size(root);
//    }
//
//private:
//    int size(Node* x) {
//        return ( x == nullptr ) ? 0 : x->nodeSize;
//    }

    //
    // Insertion d'une paire cle / valeur.
    //
public:
    void put(const std::string& key) {
        root = put(root, key, 0);
    }

private:
    Node* put(Node* x, const std::string& key, size_t d) {
        if (x==nullptr)
            x = new Node(key[d], false);

        if (key[d] < x->c)
            x->left = put(x->left, key, d);
        else if (key[d] > x->c)
            x->right = put(x->right, key, d);
        else if (d < key.length() - 1)
            x->center = put(x->center, key, d + 1);
        else {
            x->end = true; nbElements++;}


//        updateNodeSize(x);

//        return x;  // AVL. sinon on aurait return x;
        return restoreBalance(x);  // AVL. sinon on aurait return x;
    }

    //
    // AVL: calcul et restoration de l'équilibre d'un noeud.
    //
    int balance(Node* x) {
        if(x==nullptr) return 0;
        return height(x->left) - height(x->right);
    }
    Node* restoreBalance(Node* x) {

        if(balance(x) < -1) // left < right-1
        {
            if (balance(x->right)>0)
                x->right = rotateRight( x->right );
            x = rotateLeft(x);
        }
        else if( balance(x) > 1) // left > right+1
        {
            if ( balance(x->left) < 0 )
                x->left = rotateLeft( x->left );
            x = rotateRight(x);
        }
        else updateNodeHeight(x);
        return x;
    }

    //
    // Recherche d'une cle. Renvoie true et modifie
    // value si la cle est trouvee. Renvoie false et
    // ne modifie pas value sinon.
    //
public:
    bool contains( const std::string& key ) {
        return get(key);
    }

    //
    // Profondeur de l'arbre.
    //
public:
    int height()
    {
        return height(root);
    }
private:
    int height(Node* x) {
        if ( x == nullptr )
            return -1;
        return x->nodeHeight;
    }

public:
    bool get(const std::string& key) {
        Node* x = get(root, key, 0);

        if (x == nullptr)
            return false;

        return x->end;
    }

private:
    Node* get(Node* x, const std::string& key, size_t d) {
        if (x == nullptr)
            return nullptr;

        if (key[d] < x->c)
            return get(x->left, key, d);
        else if (key[d] > x->c)
            return get(x->right, key, d);
        else if (d < key.length() - 1)
            return get(x->center, key, d + 1);
        else
            return x;
    }

};

#endif //LABO5_TERNARYSEARCHTREE_H
