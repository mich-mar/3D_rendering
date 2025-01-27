#ifndef MATH_H
#define MATH_H

#include <vector>
#include <algorithm>
#include <string>
#include "matrix4x4.h"

/**
 * @class mesh
 * @brief Represents a 3D mesh, composed of triangles, with utility functions for transformation, loading, and saving.
 */
struct mesh {
    std::vector<triangle3D> triangles; ///< List of triangles making up the mesh

public:
    mesh() = default;

    void addTriangle(const triangle3D& tri);
    // void applyTransform(const matrix4x4& transform);
    bool loadObj(const std::string& filename);
    void saveObj(const std::string& filename) const;
    void generateCube();
    void printTriangles() const;
    // void clear();
    // size_t getTriangleCount() const;
    // const std::vector<triangle>& getTriangles() const;
};

#endif // MATH_H
