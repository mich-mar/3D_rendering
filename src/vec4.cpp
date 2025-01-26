#include "vec4.h"

/**
     * @brief Default constructor for vec4.
     * Initializes the vector components to 0.
*/
vec4::vec4() : x(0), y(0), z(0), w(0) {
}

vec4::vec4(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w) {
}
/**
    * @brief Normalizes a given 4D vector.
    * @param v The vector to normalize.
    * @return A normalized version of the input vector.
*/
vec4 vec4::normalize(vec4 v) {
    float magnitude = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    if (magnitude == 0) {
        return vec4(0, 0, 0, 0); // zwróć wektor zerowy jeśli długość wynosi 0
    }
    return vec4(v.x / magnitude, v.y / magnitude, v.z / magnitude, v.w / magnitude);
}

/**
    * @brief Adds two 4D vectors.
    * @param v The vector to add to this vector.
    * @return The result of the addition.
*/
vec4 vec4::operator+(vec4 v) {
    return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
}

/**
     * @brief Subtracts one 4D vector from another.
     * @param v The vector to subtract from this vector.
     * @return The result of the subtraction.
*/
vec4 vec4::operator-(vec4 v) {
    return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
}

/**
     * @brief Multiplies two 4D vectors component-wise.
     * @param v The vector to multiply with this vector.
     * @return The result of the multiplication.
*/
vec4 vec4::operator*(vec4 v) {
    return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
}

/**
     * @brief Divides two 4D vectors component-wise.
     * @param v The vector to divide this vector by.
     * @return The result of the division.
*/
vec4 vec4::operator/(vec4 v) {
    return vec4(
        v.x != 0 ? x / v.x : 0,
        v.y != 0 ? y / v.y : 0,
        v.z != 0 ? z / v.z : 0,
        v.w != 0 ? w / v.w : 0
    );
}

/**
     * @brief Sets the components of the vector.
     * @param x The new x-component of the vector.
     * @param y The new y-component of the vector.
     * @param z The new z-component of the vector.
     * @param w The new w-component of the vector.
*/
void vec4::setVec4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}