#include "render.h"

void MultiplyMatrixVector(vec3D &i, vec3D &o, matrix4x4 &m) {
    o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
    o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
    o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
    float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

    if (w != 0.0f) {
        o.x /= w;
        o.y /= w;
        o.z /= w;
    }
}

triangle3D rot(triangle3D &tri, matrix4x4 &matrixRot) {
    triangle3D tempTri;

    tempTri.p[0] = multiplyMatrixByVector(tri.p[0], matrixRot);
    tempTri.p[1] = multiplyMatrixByVector(tri.p[1], matrixRot);
    tempTri.p[2] = multiplyMatrixByVector(tri.p[2], matrixRot);

    return tempTri;
}

float depth = 8.0f;

triangle3D transXY(triangle3D &tri) {
    triangle3D triTranslated = tri;

    triTranslated.p[0].z = tri.p[0].z + depth;
    triTranslated.p[1].z = tri.p[1].z + depth;
    triTranslated.p[2].z = tri.p[2].z + depth;

    return triTranslated;
}

// Przeciążony konstruktor klasy render z argumentami dla szerokości i wysokości okna
render::render(float windowHeight, float windowWidth, const std::string &filename) : sfml(
    windowWidth, windowHeight, "3D rendering") {
    // Generowanie siatki sześcianu
    meshObject.loadObj(filename);
    // meshObject.generateCube();


    // Obliczanie stosunku szerokości do wysokości okna
    fAspectRatio = static_cast<float>(windowHeight) / windowWidth;

    // Obliczanie współczynnika FOV (Field of View) w radianach
    fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
}

// Funkcja renderująca widok 2D
void render::render2Dview() {
    trianglesToRaster.clear();

    // Czyszczenie ekranu i ustawienie koloru tła na szary
    sfml.clearScreen({0, 0, 0});

    // Generowanie macierzy projekcji
    projection = genProjectionMatrix(fNear, fFar, fAspectRatio, fFovRad);


    // Ustalanie kąta rotacji zmieniającego się w czasie (zależnego od ctr)
    rotAngle += static_cast<float>(ctr) * 0.00001f;

    // Generowanie macierzy rotacji wzdłuż osi X i Z
    MatrixRotX = genRotationX(rotAngle);
    MatrixRotZ = genRotationZ(rotAngle / 2);

    vec3D camera;

    std::vector<triangle3D> vecTrianglesToRaster;


    // Iteracja przez wszystkie trójkąty w siatce sześcianu
    for (auto tri: meshObject.triangles) {
        triangle3D triProjected, triTranslated, triRotatedZ, triRotatedZX;

        // Rotate in Z-Axis
        triRotatedZ = rot(tri, MatrixRotZ);

        // Rotate in X-Axis
        triRotatedZX = rot(triRotatedZ, MatrixRotX);

        // Offset into the screen
        triTranslated = transXY(triRotatedZX);

        // Use Cross-Product to get surface normal
        // vec3D normal;

        normal = normalVec(triTranslated);

        //if (normal.z < 0)
        if (dotProduct(normal, triTranslated.p[0]) < 0.0f) {
            // Illumination
            vec3D light_direction = {0.0f, 0.0f, -1.0f};

            float ll = sqrtf(
                light_direction.x * light_direction.x + light_direction.y * light_direction.y + light_direction.z *
                light_direction.z);
            light_direction.x /= ll;
            light_direction.y /= ll;
            light_direction.z /= ll;

            // How similar is normal to light direction
            float dp = normal.x * light_direction.x + normal.y * light_direction.y + normal.z * light_direction.z;

            triProjected.color = generateRGB(dp);

            // Project triangles from 3D --> 2D
            MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], projection);
            MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], projection);
            MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], projection);
            // @todo: nie działa
            // triTranslated.p[0] = multiplyMatrixByVector(triTranslated.p[0],projection);
            // triTranslated.p[1] = multiplyMatrixByVector(triTranslated.p[1],projection);
            // triTranslated.p[2] = multiplyMatrixByVector(triTranslated.p[2],projection);
            // triTranslated.p[0].normalize();
            // triTranslated.p[1].normalize();
            // triTranslated.p[2].normalize();


            // Scale into view
            triProjected.p[0].x += 1.0f;
            triProjected.p[0].y += 1.0f;
            triProjected.p[1].x += 1.0f;
            triProjected.p[1].y += 1.0f;
            triProjected.p[2].x += 1.0f;
            triProjected.p[2].y += 1.0f;
            triProjected.p[0].x *= 0.5f * (float) sfml.windowWidth;
            triProjected.p[0].y *= 0.5f * (float) sfml.windowHeight;
            triProjected.p[1].x *= 0.5f * (float) sfml.windowWidth;
            triProjected.p[1].y *= 0.5f * (float) sfml.windowHeight;
            triProjected.p[2].x *= 0.5f * (float) sfml.windowWidth;
            triProjected.p[2].y *= 0.5f * (float) sfml.windowHeight;

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

    for (auto &triProjected: vecTrianglesToRaster) {
        point2D p1 = {triProjected.p[0].x, triProjected.p[0].y};
        point2D p2 = {triProjected.p[1].x, triProjected.p[1].y};
        point2D p3 = {triProjected.p[2].x, triProjected.p[2].y};

        // Rasterize triangle
        sfml.fillTriangle(p1, p2, p3, triProjected.color);
    }

    // Obsługa zdarzeń SFML
    sfml.handleEvents();

    // Aktualizacja ekranu po renderowaniu
    sfml.updateScreen();

    // Licznik czasu / klatek
    ctr++;
}

// void render::rotX(triangle3D &tri, matrix4x4 &MatrixRotX) {
//     // Rotate in X-Axis
//     tri.p[0] = multiplyMatrixByVector(tri.p[0], MatrixRotX);
//     tri.p[1] = multiplyMatrixByVector(tri.p[1], MatrixRotX);
//     tri.p[2] = multiplyMatrixByVector(tri.p[2], MatrixRotX);
//     // tri.p[0].normalize();
//     // tri.p[1].normalize();
//     // tri.p[2].normalize();
// }
//
// void render::transXY(triangle3D &tri) {
//     // Offset into the screen
//     tri.p[0].z = tri.p[0].z + DepthOffset;
//     tri.p[1].z = tri.p[1].z + DepthOffset;
//     tri.p[2].z = tri.p[2].z + DepthOffset;
// }
