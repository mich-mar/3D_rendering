#ifndef MATH3D_H
#define MATH3D_H

#include "vec3D.h"
#include "matrix4x4.h"
#include "triangle3D.h"

vec3D normalVec(const triangle3D& tri);

vec3D normalVec(vec3D& vec1, vec3D& vec2);

float dotProduct(vec3D& vec1, vec3D& vec2);

float length(vec3D &v);

matrix4x4 genRotationX(float angleRad);

matrix4x4 genRotationY(float angleRad);

matrix4x4 genRotationZ(float angleRad);

vec3D multiplyMatrixByVector(const vec3D &vector, const matrix4x4 &matrix);

matrix4x4 genProjectionMatrix(float fNear, float fFar, float aspectRatio, float fFovRad);



#endif //MATH3D_H
