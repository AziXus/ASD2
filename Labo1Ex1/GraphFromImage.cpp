#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    /* A IMPLEMENTER */
}

// throws std::out_of_range
GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    if (v > V())
        throw std::out_of_range("index invalide");

    Iterable adj;

    if (y(v) > 0) { //Pixel supérieur (pas sur la première ligne)
        if (estMemeCouleur(v, v - image.width()))
            adj.push_back(v - image.width());
    }

    if (y(v) < image.height() - 1) { //Pixel inférieur (pas sur la dernière ligne)
        if (estMemeCouleur(v, v + image.width()))
            adj.push_back(v + image.width());
    }

    if (x(v) > 0) { //Pixel de gauche (pas sur la première colonne)
        if (estMemeCouleur(v, v - 1))
            adj.push_back(v - 1);
    }

    if (x(v) < image.width() - 1) { //Pixel de droite (pas sur la dernière colonne)
        if (estMemeCouleur(v, v + 1))
            adj.push_back(v + 1);
    }


    return adj;
    //Retourne les pixels adjacents de la meme couleur
    /* A IMPLEMENTER */
}

// throws std::out_of_range
int GraphFromImage::idx(int x, int y) const {
    //Retourner un index fonctionnel pour le parcours utilisant un vecteur "marked"

    if (x < 0 or x > (int)image.width())
        throw std::out_of_range("x est en dehors de l'image");

    if (y < 0 or y > (int)image.height())
        throw std::out_of_range("y est en dehors de l'image");

    return y * (int)image.width() + x;
}

// throws std::out_of_range
int GraphFromImage::x(int idx) const {

    if (idx > V())
        throw std::out_of_range("l'index est en dehors de l'image");

    int posX = idx - ((int)image.width() * y(idx));

    return posX;

    /* A IMPLEMENTER */
}

// throws std::out_of_range
int GraphFromImage::y(int idx) const {
    //idx = y * WIDTH + x => y = (idx - x) / WIDTH

    if (idx > V())
        throw std::out_of_range("l'index est en dehors de l'image");

    int posY = idx / (int)image.width();

    return posY;

    /* A IMPLEMENTER */
}

int GraphFromImage::V() const {
    return (int)image.height() * (int)image.width();
}

bool GraphFromImage::estMemeCouleur(int idx1, int idx2) const {
    unsigned char r1, r2, g1, g2, b1, b2;

    image.get_pixel((unsigned)x(idx1), (unsigned)y(idx1), r1, g1, b1);
    image.get_pixel((unsigned)x(idx2), (unsigned)y(idx2), r2, g2, b2);

    return r1 == r2 and g1 == g2 and b1 == b2;
}
