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

    std::vector<vec3> vertices; // Lista wierzchołków
    std::vector<vec3> normals; // Lista wektorów normalnych
    std::string line;

    triangles.clear(); // Wyczyszczenie listy trójkątów

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            // Wczytanie wierzchołka
            vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (prefix == "vn") {
            // Wczytanie wektora normalnego
            vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (prefix == "f") {
            // Wczytanie trójkąta
            int vertexIndices[3]; // Indeksy wierzchołków
            int normalIndices[3]; // Indeksy normalnych
            char slash;

            // Parsowanie linii `f` w formacie `1//1 2//2 3//3`
            for (int i = 0; i < 3; ++i) {
                iss >> vertexIndices[i] >> slash >> slash >> normalIndices[i];
            }

            // Walidacja indeksów
            for (int i = 0; i < 3; ++i) {
                if (vertexIndices[i] <= 0 || vertexIndices[i] > vertices.size()) {
                    std::cerr << "Error: Vertex index out of range in file " << filename << std::endl;
                    // return false;
                 }
                if (normalIndices[i] <= 0 || normalIndices[i] > normals.size()) {
                    std::cerr << "Error: Normal index out of range in file " << filename << std::endl;
                    // return false;
                }
            }

            // Tworzenie trójkąta z wierzchołków (ignorujemy normalne w tej wersji)
            triangle tri = {
                vertices[vertexIndices[0] - 1],
                vertices[vertexIndices[1] - 1],
                vertices[vertexIndices[2] - 1]
            };
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
    for (const auto &tri: triangles) {
        std::cout << "Triangle:\n";
        std::cout << "  Vertex 0: (" << tri.p[0].x << ", " << tri.p[0].y << ", " << tri.p[0].z << ")\n";
        std::cout << "  Vertex 1: (" << tri.p[1].x << ", " << tri.p[1].y << ", " << tri.p[1].z << ")\n";
        std::cout << "  Vertex 2: (" << tri.p[2].x << ", " << tri.p[2].y << ", " << tri.p[2].z << ")\n";
    }
}
