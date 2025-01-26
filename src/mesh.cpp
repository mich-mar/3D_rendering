#include "mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Adds a triangle to the mesh.
 * @param tri The triangle to add.
 */
void mesh::addTriangle(const triangle &tri) {
    triangles.push_back(tri);
}

/**
 * @brief Loads a mesh from an .obj file.
 * @param filename The path to the .obj file.
 * @return True if the file is successfully loaded; false otherwise.
 */
bool mesh::loadObj(const std::string &filename) {
    std::cout << "Loading OBJ file " << filename << std::endl;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::vector<vec3> vertices;
    std::string line;

    triangles.clear();

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") { // Vertex
            vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (prefix == "f") { // Face
            int indices[3];
            iss >> indices[0] >> indices[1] >> indices[2];
            triangle tri = {vertices[indices[0] - 1], vertices[indices[1] - 1], vertices[indices[2] - 1]};
            addTriangle(tri);
        }
    }

    file.close();
    return true;
}


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

void mesh::printTriangles() const {
    // Wypisanie wszystkich trójkątów
    for (const auto& tri : triangles) {
        std::cout << "Triangle:\n";
        std::cout << "  Vertex 0: (" << tri.p[0].x << ", " << tri.p[0].y << ", " << tri.p[0].z << ")\n";
        std::cout << "  Vertex 1: (" << tri.p[1].x << ", " << tri.p[1].y << ", " << tri.p[1].z << ")\n";
        std::cout << "  Vertex 2: (" << tri.p[2].x << ", " << tri.p[2].y << ", " << tri.p[2].z << ")\n";
    }
}
