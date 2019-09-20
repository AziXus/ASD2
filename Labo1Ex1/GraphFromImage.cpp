#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
//    for (unsigned x = 0; x < i.width(); ++x) {
//        for (unsigned y = 0; y < i.height(); ++y) {
//            //Ajouter sommets
//        }
//    }
    /* A IMPLEMENTER */
}

// throws std::out_of_range
GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    //Retourne les pixels adjacents de la meme couleur
    /* A IMPLEMENTER */
}

// throws std::out_of_range
int GraphFromImage::idx(int x, int y) const {
    //Retourner un index fonctionnel pour le parcours utilisant un vecteur "marked"

    return y * image.width() + x;

    /* A IMPLEMENTER */
}

// throws std::out_of_range
int GraphFromImage::x(int idx) const {

    /* A IMPLEMENTER */
}

// throws std::out_of_range
int GraphFromImage::y(int idx) const {
    //idx = y * WIDTH + x => y = (idx - x) / WIDTH

    /* A IMPLEMENTER */
}

int GraphFromImage::V() const {
    /* A IMPLEMENTER */
}
