#ifndef MATH_H
#define MATH_H

#include <vector>

    struct vec3D {
        float x, y, z;
    };

    struct triangle {
        vec3D p[3];
    };

    struct mesh {
        std::vector<triangle> triangles;
    };

#endif // MATH_H
