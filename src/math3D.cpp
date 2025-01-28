//
// Created by michal on 27.01.25.
//

#include "math3D.h"


vec3D normalVec(const vec3D &vec1, const vec3D &vec2) {
    vec3D result;

    result.x = vec1.y * vec2.z - vec1.z * vec2.y;
    result.y = vec1.z * vec2.x - vec1.x * vec2.z;
    result.z = vec1.x * vec2.y - vec1.y * vec2.x;

    float len = sqrtf(result.x * result.x + result.y * result.y + result.z * result.z);

    result.x /= len;
    result.y /= len;
    result.z /= len;

    return result;
}

vec3D normalVec(const triangle3D &tri) {
    vec3D result, vec1, vec2;

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
   * @brief Creates a projection matrix.
   * @return A new projection matrix.
*/
matrix4x4 genProjectionMatrix(float fNear, float fFar, float fAspectRatio, float fFovRad) {
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
vec3D multiplyMatrixByVector(const vec3D &vector, const matrix4x4 &m) {
    vec3D result;

    result.x = vector.x * m.m[0][0] + vector.y * m.m[1][0] + vector.z * m.m[2][0] + vector.w * m.m[3][0];
    result.y = vector.x * m.m[0][1] + vector.y * m.m[1][1] + vector.z * m.m[2][1] + vector.w * m.m[3][1];
    result.z = vector.x * m.m[0][2] + vector.y * m.m[1][2] + vector.z * m.m[2][2] + vector.w * m.m[3][2];
    result.w = vector.x * m.m[0][3] + vector.y * m.m[1][3] + vector.z * m.m[2][3] + vector.w * m.m[3][3];

    // float w = vector.x * m.m[0][3] + vector.y * m.m[1][3] + vector.z * m.m[2][3] + m.m[3][3];
    //
    // if (w != 0.0f) {
    //     result.x = vector.x / w;
    //     result.y = vector.y / w;
    //     result.z = vector.z / w;
    // }
    return result;
}

float dotProduct(vec3D &v1, vec3D &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
