#include "render.h"

triangle3D render::rot(triangle3D &tri, matrix4x4 &matrixRot) {
    triangle3D tempTri;

    tempTri.p[0] = multiplyMatrixByVector(tri.p[0], matrixRot);
    tempTri.p[1] = multiplyMatrixByVector(tri.p[1], matrixRot);
    tempTri.p[2] = multiplyMatrixByVector(tri.p[2], matrixRot);

    return tempTri;
}


triangle3D render::transXY(triangle3D &tri) {
    triangle3D triTranslated = tri;

    triTranslated.p[0].z = tri.p[0].z + depthOffset;
    triTranslated.p[1].z = tri.p[1].z + depthOffset;
    triTranslated.p[2].z = tri.p[2].z + depthOffset;

    return triTranslated;
}

triangle3D render::triScale(triangle3D &tri) {
    triangle3D triProjected = tri;

    // Przesunięcie współrzędnych
    for (int i = 0; i < 3; ++i) {
        triProjected.p[i].x += Xoffset;
        triProjected.p[i].y += Yoffset;
    }

    // Skalowanie współrzędnych do rozmiaru okna
    for (int i = 0; i < 3; ++i) {
        triProjected.p[i].x *= 0.5f * windowWidth;
        triProjected.p[i].y *= 0.5f * windowHeight;
    }

    return triProjected;
}

triangle3D render::transformTriangle3D(const triangle3D &triTranslated, const matrix4x4 &projection) {
    triangle3D triProjected = triTranslated;

    // Przemnożenie każdego wierzchołka przez macierz projekcji
    triProjected.p[0] = multiplyMatrixByVector(triTranslated.p[0], projection);
    triProjected.p[1] = multiplyMatrixByVector(triTranslated.p[1], projection);
    triProjected.p[2] = multiplyMatrixByVector(triTranslated.p[2], projection);
    triProjected.p[0] /= triProjected.p[0].w;
    triProjected.p[1] /= triProjected.p[1].w;
    triProjected.p[2] /= triProjected.p[2].w;

    return triProjected;
}

void render::setParam(float fNear, float fFar, float fFov) {
    this->fFar = fFar;
    this->fNear = fNear;
    this->fFov = fFov;
}

void render::setOffsets(float Xoffset, float Yoffset, float depthOffset) {
    this->Xoffset = Xoffset;
    this->Yoffset = Yoffset;
    this->depthOffset = depthOffset;
}

void render::setScale(float objScale) {
    this->objScale = objScale;
}


// Przeciążony konstruktor klasy render z argumentami dla szerokości i wysokości okna
render::render(float windowHeight, float windowWidth, const std::string &filename)
    : sfml(windowHeight, windowWidth, "3D Render") {
    bool result = false;

    if (filename != "-") {
        result = meshObject.loadObj(filename);
    } else {
        meshObject.generateCube();
        Xoffset = 1.0f;
        Yoffset = 1.0f;
        objScale = 0.5f;
        depthOffset = 3.0f;
    }

    if (!result) {
        exit(EXIT_FAILURE);
    }

        // Obliczanie stosunku szerokości do wysokości okna
        fAspectRatio = static_cast<float>(windowHeight) / windowWidth;

    // Obliczanie współczynnika FOV (Field of View) w radianach
    fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
}


// Funkcja renderująca widok 2D
std::vector<triangle3D> render::render2Dview(float angX, float angY, float angZ, mesh& meshObject) {
    trianglesToRaster.clear();

    // Czyszczenie ekranu i ustawienie koloru tła na szary
    // sfml.clearScreen({0, 0, 0});

    // Generowanie macierzy projekcji
    projection = genProjectionMatrix(fNear, fFar, fAspectRatio, fFovRad);

    // Ustalanie kąta rotacji zmieniającego się w czasie (zależnego od ctr)
    // rotAngle += 0.01f;

    // Generowanie macierzy rotacji wzdłuż osi X i Z
    MatrixRotX = genRotationX(angX);
    MatrixRotY = genRotationY(angY);
    MatrixRotZ = genRotationZ(angZ);

    matrix4x4 matrixTrans = genTranslationMatrix(0, 0, 0);

    std::vector<triangle3D> vecTrianglesToRaster;


    // Iteracja przez wszystkie trójkąty w siatce sześcianu
    for (auto tri: meshObject.triangles) {
        triangle3D triProjected, triTranslated, triRotatedZ, triRotatedZX, triRotatedZXY;

        // Rotate in Z-Axis
        triRotatedZ = rot(tri, MatrixRotZ);

        // Rotate in X-Axis
        triRotatedZX = rot(triRotatedZ, MatrixRotX);

        // Rotate in Y-Axis
        triRotatedZXY = rot(triRotatedZX, MatrixRotY);

        // Offset into the screen
        triTranslated = transXY(triRotatedZXY);

        // Use Cross-Product to get surface normal
        normal = normalVec(triTranslated);

        //if (normal.z < 0)
        if (dotProduct(normal, triTranslated.p[0]) < 0.0f) {
            // Illumination
            vec3D light_direction = {0.0f, 0.0f, -1.0f};

            light_direction.normalize();

            // How similar is normal to light direction
            float dp = normal.x * light_direction.x + normal.y * light_direction.y + normal.z * light_direction.z;

            triTranslated.color = generateRGB(dp);

            // Project triangles from 3D --> 2D
            triProjected = transformTriangle3D(triTranslated, projection);

            // Scale into view
            triProjected = triScale(triProjected);

            // Store triangle for sorting
            vecTrianglesToRaster.push_back(triProjected);
        }
    }

    // Sort triangles from back to front
    sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](triangle3D &t1, triangle3D &t2) {
        float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
        float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
        return z1 > z2;
    });

    // for (auto &triProjected: vecTrianglesToRaster) {
    //     point2D p1 = {triProjected.p[0].x, triProjected.p[0].y};
    //     point2D p2 = {triProjected.p[1].x, triProjected.p[1].y};
    //     point2D p3 = {triProjected.p[2].x, triProjected.p[2].y};
    //
    //     // Rasterize triangle
    //     sfml.fillTriangle(p1, p2, p3, triProjected.color);
    // }
    //
    // // Obsługa zdarzeń SFML
    // sfml.handleEvents();
    //
    // // Aktualizacja ekranu po renderowaniu
    // sfml.updateScreen();

    // sfml.renderTriangles(trianglesToRaster);

    return vecTrianglesToRaster;
}

void render::render2Dview(float angX, float angY, float angZ) {
    render2Dview(angX, angY, angZ, this->meshObject);
}