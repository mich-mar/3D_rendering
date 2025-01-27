#include "matrix4x4.h"

/**
     * @brief Copy constructor.
     * @param other The matrix4x4 object to copy from.
     */
matrix4x4::matrix4x4(const matrix4x4 &other) {
    std::memcpy(m, other.m, sizeof(m));
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
     * @brief Multiplies two 4x4 matrices.
     * @param other The matrix to multiply with.
     * @return A new matrix4x4 object that is the result of the multiplication.
*/
matrix4x4 matrix4x4::operator*(const float &val) const {
    matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * val;
            }
        }
    }
    return result;
}
