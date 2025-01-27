#include "matrix4x4.h"

/**
    * @brief Default constructor that initializes the matrix as an identity matrix.
    * @details Identity matrix has 1's on the diagonal and 0's elsewhere.
    */
matrix4x4::matrix4x4() {
    for (auto & i : m) {
        for (float & j : i) {
            j = 0.0f;
        }
    }
}

/**
     * @brief Copy constructor.
     * @param other The matrix4x4 object to copy from.
     */
matrix4x4::matrix4x4(const matrix4x4 &other) {
    std::memcpy(m, other.m, sizeof(m));
}

/**
     * @brief Generates a translation matrix.
     * @param x Translation along the X axis.
     * @param y Translation along the Y axis.
     * @param z Translation along the Z axis.
     * @return A matrix4x4 object representing the translation.
     */
matrix4x4 matrix4x4::genTranslation(float x, float y, float z) {
    matrix4x4 result;
    result.m[0][3] = x;
    result.m[1][3] = y;
    result.m[2][3] = z;
    return result;
}

/**
     * @brief Generates a scaling matrix.
     * @param x Scaling factor along the X axis.
     * @param y Scaling factor along the Y axis.
     * @param z Scaling factor along the Z axis.
     * @return A matrix4x4 object representing the scaling transformation.
     */
matrix4x4 matrix4x4::genScale(float x, float y, float z) {
    matrix4x4 result;
    result.m[0][0] = x;
    result.m[1][1] = y;
    result.m[2][2] = z;
    return result;
}

/**
    * @brief Generates a rotation matrix around the X axis.
    * @param angleRad Rotation angle in degrees.
    * @return A matrix4x4 object representing the rotation.
    */
matrix4x4 genRotationX(const float angleRad) {
    matrix4x4 result;

    result.m[0][0] = 1;
    result.m[1][1] = cosf(angleRad);
    result.m[1][2] = sinf(angleRad);
    result.m[2][1] = -sinf(angleRad);
    result.m[2][2] = cosf(angleRad);
    result.m[3][3] = 1;

    return result;
}

/**
    * @brief Generates a rotation matrix around the Y axis.
    * @param angleRad Rotation angle in degrees.
    * @return A matrix4x4 object representing the rotation.
    */
matrix4x4 genRotationY(const float angleRad) {
    matrix4x4 result;

    float cosA = std::cos(angleRad);
    float sinA = std::sin(angleRad);

    result.m[0][0] = cosA;
    result.m[0][2] = sinA;
    result.m[2][0] = -sinA;
    result.m[2][2] = cosA;

    return result;
}

/**
     * @brief Generates a rotation matrix around the Z axis.
     * @param angleRad Rotation angle in degrees.
     * @return A matrix4x4 object representing the rotation.
     */
matrix4x4 genRotationZ(float angleRad) {
    matrix4x4 result;

    result.m[0][0] = cosf(angleRad);
    result.m[0][1] = sinf(angleRad);
    result.m[1][0] = -sinf(angleRad);
    result.m[1][1] = cosf(angleRad);
    result.m[2][2] = 1;
    result.m[3][3] = 1;

    return result;
}

/**
     * @brief Multiplies two 4x4 matrices.
     * @param other The matrix to multiply with.
     * @return A new matrix4x4 object that is the result of the multiplication.
*/
matrix4x4 matrix4x4::operator*(const matrix4x4 &other) const {
    matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

/**
   * @brief Transposes the matrix.
   * @return A new matrix4x4 object that is the transpose of the current matrix.
*/
matrix4x4 matrix4x4::transpose() const {
    matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[j][i];
        }
    }
    return result;
}

/**
   * @brief Creates a projection matrix.
   * @return A new projection matrix.
*/
matrix4x4 genProjection(float fNear, float fFar, float fAspectRatio, float fFovRad) {
    matrix4x4 matProj;

    matProj.m[0][0] = fAspectRatio * fFovRad;
    matProj.m[1][1] = fFovRad;
    matProj.m[2][2] = fFar / (fFar - fNear);
    matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
    matProj.m[2][3] = 1.0f;
    matProj.m[3][3] = 0.0f;

    return matProj;
}

/**
 * @brief Multiplies a 3D vector by a 4x4 matrix, applying projection and perspective divide.
 * @param vector The vec3 vector to be multiplied.
 * @param m The 4x4 transformation matrix.
 * @return The resulting vec3 after multiplication and perspective divide.
 */
vec3 multiplyMatrixVector(const vec3 &vector, const matrix4x4& m) {
    vec3 result;

    result.x = vector.x * m.m[0][0] + vector.y * m.m[1][0] + vector.z * m.m[2][0] + m.m[3][0];
    result.y = vector.x * m.m[0][1] + vector.y * m.m[1][1] + vector.z * m.m[2][1] + m.m[3][1];
    result.z = vector.x * m.m[0][2] + vector.y * m.m[1][2] + vector.z * m.m[2][2] + m.m[3][2];
    float w = vector.x * m.m[0][3] + vector.y * m.m[1][3] + vector.z * m.m[2][3] + m.m[3][3];

    if (w != 0.0f) {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }

    return result;
}
