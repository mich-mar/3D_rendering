#ifndef MATH_H
#define MATH_H

#include <vector>
#include <algorithm>
#include <string>
#include "vec4.h"
#include "matrix4x4.h"

struct vec3 {
    float x = 0;
    float y = 0;
    float z = 0;

    vec3() = default;
    vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    vec3& operator=(const vec3& other) = default; // Allow assignment
};

/**
 * @class triangle
 * @brief Represents a triangle with three vertices in 3D space.
 */
struct triangle {
    vec3 p[3];

    triangle() = default;
    triangle(const vec3& p0, const vec3& p1, const vec3& p2) {
        p[0] = p0;
        p[1] = p1;
        p[2] = p2;
    }

    triangle& operator=(const triangle& other) = default; // Allow assignment
};

/**
 * @class mesh
 * @brief Represents a 3D mesh, composed of triangles, with utility functions for transformation, loading, and saving.
 */
class mesh {
    std::vector<triangle> triangles; ///< List of triangles making up the mesh

public:
    mesh() = default;

    void addTriangle(const triangle& tri);
    void applyTransform(const matrix4x4& transform);
    bool loadObj(const std::string& filename);
    void saveObj(const std::string& filename) const;
    void generateCube();
    void clear();
    size_t getTriangleCount() const;
    const std::vector<triangle>& getTriangles() const;
};

#endif // MATH_H
