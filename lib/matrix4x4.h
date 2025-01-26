#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cstring>
#include <cmath>
#include <vec4.h>


/**
 * @class matrix4x4
 * @brief Represents a 4x4 transformation matrix for 3D graphics.
 */
class matrix4x4 {
    float m[4][4];

    public:
    matrix4x4();
    matrix4x4(const matrix4x4& other);
    matrix4x4 genTranslation(float x, float y, float z);
    matrix4x4 genScale(float x, float y, float z);
    matrix4x4 genRotationX(float angle);
    matrix4x4 genRotationY(float angle);
    matrix4x4 genRotationZ(float angle);

    matrix4x4 operator*(const matrix4x4& other) const;
    float* operator[](int index);
    const float* operator[](int index) const;
    matrix4x4 transpose() const;
    vec4 operator*(const vec4& v) const;
};



#endif //MATRIX4X4_H
