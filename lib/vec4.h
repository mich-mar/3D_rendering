//
// Created by michal on 26.01.25.
//

#ifndef VEC4_H
#define VEC4_H

#include <cmath> // do funkcji sqrt

struct vec3 {
    float x = 0;
    float y = 0;
    float z = 0;

    vec3& operator=(const vec3& other) = default; // Allow assignment
};

/**
 * @class triangle
 * @brief Represents a triangle with three vertices in 3D space.
 */
struct triangle {
    vec3 p[3];

    triangle& operator=(const triangle& other) = default; // Allow assignment
};

/**
 * @class vec4
 * @brief A class representing a 4-dimensional vector with basic operations.
 */
struct vec4 {
    float x, y, z, w;
    
    public:    
      vec4();
      vec4(float x, float y, float z, float w);
      vec4 normalize(vec4 v);
      vec4 operator+(vec4 v);
      vec4 operator-(vec4 v);
      vec4 operator*(vec4 v);
      vec4 operator/(vec4 v);
      void setVec4(float x, float y, float z, float w);
};



#endif //VEC4_H
