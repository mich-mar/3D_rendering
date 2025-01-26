#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cstring>
#include <cmath>
#include <vec4.h>
#include <math.h>


/**
 * @class matrix4x4
 * @brief Represents a 4x4 transformation matrix for 3D graphics.
 */
struct matrix4x4 {
    float m[4][4];

    public:
    matrix4x4();
    matrix4x4(const matrix4x4& other);
    matrix4x4 genTranslation(float x, float y, float z);
    matrix4x4 genScale(float x, float y, float z);
    matrix4x4 operator*(const matrix4x4& other) const;
    matrix4x4 transpose() const;
};

vec3 multiplyMatrixVector(const vec3 vector, const matrix4x4 matrix);
matrix4x4 genProjection(float fNear, float fFar, float aspectRatio, float fFovRad);
matrix4x4 genRotationX(float angleRad);
matrix4x4 genRotationY(float angleRad);
matrix4x4 genRotationZ(float angleRad);


#endif //MATRIX4X4_H
