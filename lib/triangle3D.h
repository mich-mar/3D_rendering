//
// Created by michal on 27.01.25.
//

#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include "vec3D.h"
#include "RGB.h"

/**
 * @struct triangle
 * @brief Represents a triangle with three vertices in 3D space.
 */
struct triangle3D {
    vec3D p[3];

    RGB color = {0,0,0};

    triangle3D()=default;

    triangle3D(vec3D p0, vec3D p1, vec3D p2) {
        p[0] = p0;
        p[1] = p1;
        p[2] = p2;
    };

    triangle3D &operator=(const triangle3D &other);
};

#endif //TRIANGLE3D_H
