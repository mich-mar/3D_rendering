//
// Created by michal on 26.01.25.
//

#include "matrix4x4.h"

/**
    * @brief Default constructor that initializes the matrix as an identity matrix.
    * @details Identity matrix has 1's on the diagonal and 0's elsewhere.
    */
matrix4x4::matrix4x4() {
    // Initialize as identity matrix
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = (i == j) ? 1.0f : 0.0f;
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
    * @param angle Rotation angle in degrees.
    * @return A matrix4x4 object representing the rotation.
    */
matrix4x4 matrix4x4::genRotationX(float angle) {
    matrix4x4 result;
    float rad = angle * M_PI / 180.0f; // Convert to radians
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    result.m[1][1] = cosA;
    result.m[1][2] = -sinA;
    result.m[2][1] = sinA;
    result.m[2][2] = cosA;

    return result;
}

/**
    * @brief Generates a rotation matrix around the Y axis.
    * @param angle Rotation angle in degrees.
    * @return A matrix4x4 object representing the rotation.
    */
matrix4x4 matrix4x4::genRotationY(float angle) {
    matrix4x4 result;
    float rad = angle * M_PI / 180.0f; // Convert to radians
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    result.m[0][0] = cosA;
    result.m[0][2] = sinA;
    result.m[2][0] = -sinA;
    result.m[2][2] = cosA;

    return result;
}

/**
     * @brief Generates a rotation matrix around the Z axis.
     * @param angle Rotation angle in degrees.
     * @return A matrix4x4 object representing the rotation.
     */
matrix4x4 matrix4x4::genRotationZ(float angle) {
    matrix4x4 result;
    float rad = angle * M_PI / 180.0f; // Convert to radians
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    result.m[0][0] = cosA;
    result.m[0][1] = -sinA;
    result.m[1][0] = sinA;
    result.m[1][1] = cosA;

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
    * @brief Provides access to a specific row of the matrix.
    * @param index The index of the row (0-3).
    * @return A pointer to the array representing the row.
    * @note No bounds checking is performed.
*/
float *matrix4x4::operator[](int index) {
    return m[index];
}

/**
     * @brief Provides read-only access to a specific row of the matrix.
     * @param index The index of the row (0-3).
     * @return A const pointer to the array representing the row.
     * @note No bounds checking is performed.
*/
const float *matrix4x4::operator[](int index) const {
    return m[index];
}
