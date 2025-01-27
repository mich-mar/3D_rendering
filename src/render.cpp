#include "render.h"

#include <fstream>

// Przeciążony konstruktor klasy render z argumentami dla szerokości i wysokości okna
render::render(float windowHeight, float windowWidth, const std::string& filename) : sfml(
    windowWidth, windowHeight, "3D rendering") {
    // Generowanie siatki sześcianu
    if (filename == "-")
        meshObject.generateCube();
    else
        meshObject.loadObj(filename);


    // Obliczanie stosunku szerokości do wysokości okna
    fAspectRatio = static_cast<float>(windowHeight) / windowWidth;

    // Obliczanie współczynnika FOV (Field of View) w radianach
    fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
}

// Funkcja renderująca widok 2D
void render::render2Dview() {
    trianglesToRaster.clear();

    // Czyszczenie ekranu i ustawienie koloru tła na szary
    sfml.clearScreen({100, 100, 100});

        // Generowanie macierzy projekcji
        projection = genProjection(fNear, fFar, fAspectRatio, fFovRad);


    // Ustalanie kąta rotacji zmieniającego się w czasie (zależnego od ctr)
    rotAngle += static_cast<float>(ctr) * 0.01f;

    // Generowanie macierzy rotacji wzdłuż osi X i Z
    MatrixRotX = genRotationX(rotAngle);
    MatrixRotZ = genRotationZ(rotAngle);

    // Iteracja przez wszystkie trójkąty w siatce sześcianu
    for (auto &tri: meshObject.triangles) {

        // Rotacja trójkąta wzdłuż osi Z
        triRotatedZ.p[0] = multiplyMatrixVector(tri.p[0], MatrixRotZ);
        triRotatedZ.p[1] = multiplyMatrixVector(tri.p[1], MatrixRotZ);
        triRotatedZ.p[2] = multiplyMatrixVector(tri.p[2], MatrixRotZ);

        // Rotacja wzdłuż osi X
        triRotatedZX.p[0] = multiplyMatrixVector(triRotatedZ.p[0], MatrixRotX);
        triRotatedZX.p[1] = multiplyMatrixVector(triRotatedZ.p[1], MatrixRotX);
        triRotatedZX.p[2] = multiplyMatrixVector(triRotatedZ.p[2], MatrixRotX);

        // Translacja trójkąta w osi Z (przesunięcie go do przodu)
        triTranslated = triRotatedZX;
        triTranslated.p[0].z = triRotatedZX.p[0].z + zOffset;
        triTranslated.p[1].z = triRotatedZX.p[1].z + zOffset;
        triTranslated.p[2].z = triRotatedZX.p[2].z + zOffset;

        // create normal to triangle
        normal = normalVec(triTranslated);

        if (dotProduct(normal, triTranslated.p[0] - cameraPos) < 0.0f) {
            // Ilumination
            length = lightSource.calLength();
            lightSource.x /= length;
            lightSource.y /= length;
            lightSource.z /= length;

            dp = dotProduct(normal, lightSource);

            RGB color = generateRGB(dp);

            triProjected.color = color;

            // Projekcja trójkąta 3D na płaszczyznę 2D
            triProjected.p[0] = multiplyMatrixVector(triTranslated.p[0], projection);
            triProjected.p[1] = multiplyMatrixVector(triTranslated.p[1], projection);
            triProjected.p[2] = multiplyMatrixVector(triTranslated.p[2], projection);

            // Dodanie przesunięcia w osi X i Y, aby trójkąt znalazł się w widocznym zakresie
            triProjected.p[0].x += Xoffset;
            triProjected.p[0].y += Yoffset;
            triProjected.p[1].x += Xoffset;
            triProjected.p[1].y += Yoffset;
            triProjected.p[2].x += Xoffset;
            triProjected.p[2].y += Yoffset;

            // Skalowanie trójkąta na podstawie rozmiarów okna
            triProjected.p[0].x *= objScale * (float) windowWidth;
            triProjected.p[0].y *= objScale * (float) windowHeight;
            triProjected.p[1].x *= objScale * (float) windowWidth;
            triProjected.p[1].y *= objScale * (float) windowHeight;
            triProjected.p[2].x *= objScale * (float) windowWidth;
            triProjected.p[2].y *= objScale * (float) windowHeight;

            trianglesToRaster.push_back(triProjected);

            // Rysowanie trójkąta na ekranie za pomocą SFML
            // sfml.fillTriangle(
            //     triProjected.p[0].x, triProjected.p[0].y,
            //     triProjected.p[1].x, triProjected.p[1].y,
            //     triProjected.p[2].x, triProjected.p[2].y,color
            // );

            // sfml.drawTriangle(
            //     triProjected.p[0].x, triProjected.p[0].y,
            //     triProjected.p[1].x, triProjected.p[1].y,
            //     triProjected.p[2].x, triProjected.p[2].y,{0,0,0},3.0f
            // );
        }

        // sorting triangles to raster
        sort(trianglesToRaster.begin(), trianglesToRaster.end(), [](triangle a, triangle b) {
            float z1 = (a.p[0].z + a.p[1].z + a.p[2].z) / 3.0f;
            float z2 = (b.p[0].z + b.p[1].z + b.p[2].z) / 3.0f;
            return z1 > z2;
        });

        for (auto &tri: trianglesToRaster) {
            sfml.fillTriangle(
                tri.p[0].x, tri.p[0].y,
                tri.p[1].x, tri.p[1].y,
                tri.p[2].x, tri.p[2].y, {tri.color}
            );
        }
    }

    // Obsługa zdarzeń SFML
    sfml.handleEvents();

    // Aktualizacja ekranu po renderowaniu
    sfml.updateScreen();

    // Licznik czasu / klatek
    ctr++;
}
