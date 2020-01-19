/*
 * File:   TernarySearchTree.h
 * Author: Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 * Labo 5
 *
 * Description: Classe implémentant la structure d'un TST(TernarySearchTree)
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
        int nodeHeight; // hauteur du sous-arbre dont ce noeud est la racine.
        Node(char c, bool val) : c(c), end(val), right(nullptr), center(nullptr), left(nullptr),
                                 nodeHeight(0) {}
    };

    //
    // Racine de l'arbre.
    //
    Node* root;

private:

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
    /**
     * Permet de supprimer un arbre dans sa totalité(sous-arbre gauche-droite-millieu)
     * @param x noeud duquel il faut commencé à supprimer
     */
    void deleteSubTree(Node* x) {
        if( x == nullptr) return;
        deleteSubTree( x->right );
        deleteSubTree( x->center );
        deleteSubTree( x->left );
        delete x;
    }

public:
    //
    // Insertion d'une paire cle / valeur.
    //
    void put(const std::string& key) {
        root = put(root, key, 0);
    }

private:
    /**
     * Permet d'insérer un nouveau mot dans l'arbre TST
     * @param x pointeur vers Node étant le noeud de départ
     * @param key string représenté la valeur que l'onn veut ajouter dans l'arbre
     * @param d size_t permettant de connaître l'emplacement du caractère qui est traité
     * @return le noeud de départ en ayant un arbre équilibré
     */
    Node* put(Node* x, const std::string& key, size_t d) {
        //Si le noeud est vide c'est que on est arrivé au bout de l'arbre il faut donc ajouter un nouveau noeud avec le nouveau caractère
        if (x==nullptr)
            x = new Node(key[d], false);

        if (key[d] < x->c)
            x->left = put(x->left, key, d);
        else if (key[d] > x->c)
            x->right = put(x->right, key, d);
        //Si le numéro du caractère traité est plus petit que la taille du mot(pas de dépassement de la chaîne key) alors on passe au centre
        //Passage au centre car nous sommes certains que le caractère traité est égal au noeud actuel car les 2 if précédent ont échoué
        else if (d < key.length() - 1)
            x->center = put(x->center, key, d + 1);
        else
            x->end = true;

        return restoreBalance(x);  // AVL. sinon on aurait return x;
    }

    //
    // AVL: calcul et restoration de l'équilibre d'un noeud.
    //
    int balance(Node* x) {
        if(x==nullptr) return 0;
        return height(x->left) - height(x->right);
    }

    /**
     * Permet de rendre le TST équilibré à nouveau (pas d'équilibrage avec l'arbre du milieu
     * @param x
     * @return
     */
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
    /**
     * Fonction privée récursive retournant la hauteur du noeud
     * @param x noeud à analyser
     * @return hauteur de l'arbre
     */
    int height(Node* x) {
        if ( x == nullptr )
            return -1;
        return x->nodeHeight;
    }

public:
    /**
     * Fonction publique retournant si la string est présente dans la TST
     * @param key string à rechercher dans la TST
     * @return true si la string est présente, false sinon
     */
    bool get(const std::string& key) {
        Node* x = get(root, key, 0);

        if (x == nullptr)
            return false;

        return x->end;
    }

private:
    /**
     * Fonction privée recursive retournant si la valeur est présente dans la TST
     * @param x node de départ
     * @param key string à rechercher dans le TST
     * @param d taille du mot
     * @return retourne le noeud final
     */
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
