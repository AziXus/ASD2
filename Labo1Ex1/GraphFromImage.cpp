#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    /* A IMPLEMENTER */
}

// throws std::out_of_range
GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    Iterable adj;
    for (int w = 0; w < V(); w++)
        if(adjMatrix.at(v)[w])
            adj.push_back(w);
    return adj;
}

// throws std::out_of_range
int GraphFromImage::idx(int x, int y) const {
    /* A IMPLEMENTER */
}

// throws std::out_of_range
int GraphFromImage::x(int idx) const {
    /* A IMPLEMENTER */
}

// throws std::out_of_range
int GraphFromImage::y(int idx) const {
    /* A IMPLEMENTER */
}

int GraphFromImage::V() const {
    return image.height() * image.width();
}
