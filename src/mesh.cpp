#include "mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Adds a triangle to the mesh.
 * @param tri The triangle to add.
 */
// void mesh::addTriangle(const triangle &tri) {
//     triangles.push_back(tri);
// }

/**
 * @brief Applies a transformation matrix to all vertices in the mesh.
 * @param transform The transformation matrix to apply.
 */
// void mesh::applyTransform(const matrix4x4 &transform) {
//     for (auto &tri : triangles) {
//         for (int i = 0; i < 3; ++i) {
//             vec4 v(tri.p[i].x, tri.p[i].y, tri.p[i].z, 1.0f);
//             v = transform * v;
//             tri.p[i] = {v.x, v.y, v.z};
//         }
//     }
// }

/**
 * @brief Loads a mesh from an .obj file.
 * @param filename The path to the .obj file.
 * @return True if the file is successfully loaded; false otherwise.
 */
// bool mesh::loadObj(const std::string &filename) {
//     std::ifstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Error: Could not open file " << filename << std::endl;
//         return false;
//     }
//
//     std::vector<vec3> vertices;
//     std::string line;
//
//     while (std::getline(file, line)) {
//         std::istringstream iss(line);
//         std::string prefix;
//         iss >> prefix;
//
//         if (prefix == "v") { // Vertex
//             vec3 vertex;
//             iss >> vertex.x >> vertex.y >> vertex.z;
//             vertices.push_back(vertex);
//         } else if (prefix == "f") { // Face
//             int indices[3];
//             iss >> indices[0] >> indices[1] >> indices[2];
//             triangle tri = {vertices[indices[0] - 1], vertices[indices[1] - 1], vertices[indices[2] - 1]};
//             addTriangle(tri);
//         }
//     }
//
//     file.close();
//     return true;
// }

/**
 * @brief Saves the mesh to an .obj file.
 * @param filename The path to the .obj file.
 */
// void mesh::saveObj(const std::string &filename) const {
//     std::ofstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Error: Could not open file " << filename << std::endl;
//         return;
//     }
//
//     // Write vertices
//     for (const auto &tri : triangles) {
//         for (const auto &vertex : tri.p) {
//             file << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
//         }
//     }
//
//     // Write faces
//     int vertexIndex = 1;
//     for (const auto &tri : triangles) {
//         file << "f " << vertexIndex << " " << vertexIndex + 1 << " " << vertexIndex + 2 << "\n";
//         vertexIndex += 3;
//     }
//
//     file.close();
// }

/**
 * @brief Initializes the mesh with the cube template.
 */
void mesh::generateCube() {
    triangles = {

        // SOUTH
        {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},

        // EAST
        {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},

        // NORTH
        {1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},

        // WEST
        {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},

        // TOP
        {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

        // BOTTOM
        {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    };
};


/**
 * @brief Clears all triangles in the mesh.
 * Resets the mesh to an empty state.
 */
// void mesh::clear() {
//     triangles.clear();
// }

/**
 * @brief Retrieves the number of triangles in the mesh.
 * @return The number of triangles.
 */
// size_t mesh::getTriangleCount() const {
//     return triangles.size();
// }

/**
 * @brief Accesses the triangles of the mesh.
 * @return A constant reference to the vector of triangles.
 */
// const std::vector<triangle> &mesh::getTriangles() const {
//     return triangles;
// }
