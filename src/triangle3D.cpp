//
// Created by michal on 27.01.25.
//

#include "triangle3D.h"

/**
 * @brief Operator przypisania dla struktury triangle3D.
 * Kopiuje wierzchołki oraz kolor z innego trójkąta.
 *
 * @param other Inny trójkąt, którego dane będą skopiowane.
 * @return Referencja do bieżącego obiektu.
 */
triangle3D &triangle3D::operator=(const triangle3D &other) {
    // Kopiowanie wierzchołków
    for (int i = 0; i < 3; ++i) {
        p[i] = other.p[i];
    }

    // Kopiowanie koloru
    color = other.color;

    return *this;
}
