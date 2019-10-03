/* 
 * File:   GraphFromImage.cpp
 * Author: Olivier Cuisenaire
 * Modified : Müller Robin, Delhomme Claire, Teixeira Carvalho Stéphane
 *
 * Created on 2. octobre 2014, 12:09
 *
 */
#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
}

GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    //Si l'entier demandé est plus grand que la taille du graphe l'index est invalide
    if (v >= V())
        throw std::out_of_range("index invalide");

    Iterable adj;

    if (y(v) > 0) { //Pixel supérieur (pas sur la première ligne)
        if (estMemeCouleur(v, v - (int)image.width()))
            adj.push_back(v - (int)image.width());
    }

    if (y(v) < image.height() - 1) { //Pixel inférieur (pas sur la dernière ligne)
        if (estMemeCouleur(v, v + (int)image.width()))
            adj.push_back(v + (int)image.width());
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
}

int GraphFromImage::idx(int x, int y) const {
    //Retourner un index fonctionnel pour le parcours utilisant un vecteur "marked"

    if (x < 0 or x >= (int)image.width())
        throw std::out_of_range("x est en dehors de l'image");

    if (y < 0 or y >= (int)image.height())
        throw std::out_of_range("y est en dehors de l'image");

    return y * (int)image.width() + x;
}

int GraphFromImage::x(int idx) const {
    if (idx >= V())
        throw std::out_of_range("l'index est en dehors de l'image");

    //Retourne la position x en ignorant le nombre de lignes grâce au modulo
    return idx % (int)image.width();
}

int GraphFromImage::y(int idx) const {
    if (idx >= V())
        throw std::out_of_range("l'index est en dehors de l'image");

    //La position y est le nombre de lignes de 0 à idx
    return idx / (int)image.width();
}

int GraphFromImage::V() const {
    return (int)image.pixel_count();
}

bool GraphFromImage::estMemeCouleur(int idx1, int idx2) const {
    if (idx1 == idx2)
        return true;

    unsigned char r1, r2, g1, g2, b1, b2;

    //Stocke les couleurs du pixel à idx1
    image.get_pixel((unsigned)x(idx1), (unsigned)y(idx1), r1, g1, b1);

    //Stocke les couleurs du pixel à idx2
    image.get_pixel((unsigned)x(idx2), (unsigned)y(idx2), r2, g2, b2);

    //Si toutes les composantes sont de couleurs sont égales
    return r1 == r2 and g1 == g2 and b1 == b2;
}
