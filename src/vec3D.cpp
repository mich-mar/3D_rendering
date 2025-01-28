#include "vec3D.h"


/**
 * @brief Constructor for vec3D with parameters.
 * Initializes the vector components with the given values.
 *
 * @param x The x component of the vector.
 * @param y The y component of the vector.
 * @param z The z component of the vector.
 */
vec3D::vec3D(float x, float y, float z)
    : x(x), y(y), z(z) {
}

/**
 * @brief Adds two 4D vectors.
 * @param v The vector to add to this vector.
 * @return A new vector that is the result of the addition.
 */
vec3D vec3D::operator+(const vec3D &v) const {
    return vec3D(x + v.x, y + v.y, z + v.z);
}

/**
 * @brief Adds a scalar to all components of the vector.
 * @param val The scalar value to add.
 * @return A new vector with the scalar added to all components.
 */
vec3D vec3D::operator+(const float val) const {
    return vec3D(x + val, y + val, z + val);
}

/**
 * @brief Subtracts one 4D vector from another.
 * @param v The vector to subtract from this vector.
 * @return A new vector that is the result of the subtraction.
 */
vec3D vec3D::operator-(const vec3D &v) const {
    return vec3D(x - v.x, y - v.y, z - v.z);
}

/**
 * @brief Subtracts a scalar from all components of the vector.
 * @param val The scalar value to subtract.
 * @return A new vector with the scalar subtracted from all components.
 */
vec3D vec3D::operator-(const float val) const {
    return vec3D(x - val, y - val, z - val);
}

/**
 * @brief Multiplies two 4D vectors component-wise.
 * @param v The vector to multiply with this vector.
 * @return A new vector that is the result of the multiplication.
 */
vec3D vec3D::operator*(const vec3D &v) const {
    return vec3D(x * v.x, y * v.y, z * v.z);
}

/**
 * @brief Multiplies all components of the vector by a scalar.
 * @param val The scalar value to multiply with.
 * @return A new vector with all components multiplied by the scalar.
 */
vec3D vec3D::operator*(const float val) const {
    return vec3D(x * val, y * val, z * val);
}

/**
 * @brief Divides two 4D vectors component-wise.
 * @param v The vector to divide this vector by.
 * @return A new vector that is the result of the division.
 *         Components are set to 0 if division by zero occurs.
 */
vec3D vec3D::operator/(const vec3D &v) const {
    vec3D result = vec3D(x / v.x, y / v.y, z / v.z);
    return result;
}

/**
 * @brief Divides all components of the vector by a scalar.
 * @param val The scalar value to divide by.
 * @return A new vector with all components divided by the scalar.
 *         Components are set to 0 if division by zero occurs.
 */
vec3D vec3D::operator/(const float val) const {
    vec3D result = vec3D(x / val, y / val, z / val);
    return result;
}

float vec3D::length() {
    return sqrtf(x * x + y * y + z * z);
}

/**
 * @brief Normalizes the current vector to have a magnitude of 1.
 * Modifies the vector in place. If the magnitude is 0, the vector is set to (0, 0, 0, 0).
 */
void vec3D::normalize() {
    float l = length();

    x /= l;
    y /= l;
    z /= l;
}

/**
 * @brief Copies the values of another vector to this vector.
 * @param v The vector to copy.
 * @return A reference to this vector.
 */
vec3D &vec3D::operator=(const vec3D &v) {
    if (this != &v) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }
    return *this;
}

/**
 * @brief Adds another vector to this vector component-wise.
 * @param v The vector to add.
 * @return A reference to this vector after modification.
 */
vec3D &vec3D::operator+=(const vec3D &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

/**
 * @brief Subtracts another vector from this vector component-wise.
 * @param v The vector to subtract.
 * @return A reference to this vector after modification.
 */
vec3D &vec3D::operator-=(const vec3D &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

/**
 * @brief Multiplies this vector by another vector component-wise.
 * @param v The vector to multiply with.
 * @return A reference to this vector after modification.
 */
vec3D &vec3D::operator*=(const vec3D &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

/**
 * @brief Divides this vector by another vector component-wise.
 * @param v The vector to divide by. Division by zero sets the component to 0.
 * @return A reference to this vector after modification.
 */
vec3D &vec3D::operator/=(const vec3D &v) {
    x = (v.x != 0) ? x / v.x : 0;
    y = (v.y != 0) ? y / v.y : 0;
    z = (v.z != 0) ? z / v.z : 0;
    return *this;
}

/**
 * @brief Adds a scalar to all components of this vector.
 * @param val The scalar value to add.
 * @return A reference to this vector after modification.
 */
vec3D &vec3D::operator+=(float val) {
    x += val;
    y += val;
    z += val;
    return *this;
}

/**
 * @brief Subtracts a scalar from all components of this vector.
 * @param val The scalar value to subtract.
 * @return A reference to this vector after modification.
 */
vec3D &vec3D::operator-=(float val) {
    x -= val;
    y -= val;
    z -= val;
    return *this;
}

/**
 * @brief Multiplies all components of this vector by a scalar.
 * @param val The scalar value to multiply with.
 * @return A reference to this vector after modification.
 */
vec3D &vec3D::operator*=(float val) {
    x *= val;
    y *= val;
    z *= val;
    return *this;
}

/**
 * @brief Divides all components of this vector by a scalar.
 * @param val The scalar value to divide by. Division by zero sets components to 0.
 * @return A reference to this vector after modification.
 */
vec3D &vec3D::operator/=(float val) {
    x /= val;
    y /= val;
    z /= val;

    return *this;
}
