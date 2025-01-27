#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cstring>
#include <cmath>
#include <vec3D.h>
#include <triangle3D.h>


/**
 * @class matrix4x4
 * @brief Represents a 4x4 transformation matrix for 3D graphics.
 */
struct matrix4x4 {
    float m[4][4] = {0.0f};

public:
    matrix4x4() = default;

    matrix4x4(const matrix4x4 &other);

    matrix4x4 operator*(const matrix4x4 &other) const;

    matrix4x4 operator*(const float &val) const;
};


#endif //MATRIX4X4_H
