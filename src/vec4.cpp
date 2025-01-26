#include "vec4.h"

#include <render.h>

/**
     * @brief Default constructor for vec4.
     * Initializes the vector components to 0.
*/
vec4::vec4() : x(0), y(0), z(0), w(0) {
}

/**
     * @brief Default constructor for vec4.
     * @param x
     * @param y
     * @param z
     * @param w
     * Initializes the vector components with args.
*/
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
        return vec4(0, 0, 0, 0);
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

vec3 normalVec(vec3 vec1, vec3 vec2) {
    vec3 result;

    result.x = vec1.y * vec2.z - vec1.z * vec2.y;
    result.y = vec1.z * vec2.x - vec1.x * vec2.z;
    result.z = vec1.x * vec2.y - vec1.y * vec2.x;

    float len = sqrtf(result.x * result.x + result.y * result.y + result.z * result.z);

    result.x /= len;
    result.y /= len;
    result.z /= len;

    return result;
}

vec3 normalVec(triangle tri) {
    vec3 result, vec1, vec2;

    vec1.x = tri.p[1].x - tri.p[0].x;
    vec1.y = tri.p[1].y - tri.p[0].y;
    vec1.z = tri.p[1].z - tri.p[0].z;

    vec2.x = tri.p[2].x - tri.p[0].x;
    vec2.y = tri.p[2].y - tri.p[0].y;
    vec2.z = tri.p[2].z - tri.p[0].z;

    result.x = vec1.y * vec2.z - vec1.z * vec2.y;
    result.y = vec1.z * vec2.x - vec1.x * vec2.z;
    result.z = vec1.x * vec2.y - vec1.y * vec2.x;

    float len = sqrtf(result.x * result.x + result.y * result.y + result.z * result.z);

    result.x /= len;
    result.y /= len;
    result.z /= len;

    return result;
}

float dotProduct(vec3 vec1, vec3 vec2) {
    float result = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    return result;
}

vec3 vec3::operator-(const vec3 &other) const {
    return vec3{
        x - other.x,
        y - other.y,
        z - other.z
    };
}

float vec3::calLength() const {
    return sqrtf(x * x + y * y + z * z);
}



