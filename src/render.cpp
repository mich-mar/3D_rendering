#include "render.h"

// Konstruktor domyślny klasy render
render::render() : sfml(windowWidth, windowHeight, "3D rendering") {
    // Generowanie siatki sześcianu
    meshCube.generateCube();

    // Obliczanie stosunku szerokości do wysokości okna
    fAspectRatio = static_cast<float>(windowHeight) / windowWidth;

    // Obliczanie współczynnika FOV (Field of View) w radianach
    fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
}

// Przeciążony konstruktor klasy render z argumentami dla szerokości i wysokości okna
render::render(float windowHeight, float windowWidth) : sfml(windowWidth, windowHeight, "3D rendering") {
    // Generowanie siatki sześcianu
    meshCube.generateCube();

    // Obliczanie stosunku szerokości do wysokości okna
    fAspectRatio = static_cast<float>(windowHeight) / windowWidth;

    // Obliczanie współczynnika FOV (Field of View) w radianach
    fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
}

// Funkcja renderująca widok 2D
void render::render2Dview() {
    // Licznik czasu / klatek
    ctr++;

    // Czyszczenie ekranu i ustawienie koloru tła na szary
    sfml.clearScreen({100, 100, 100});

    // Generowanie macierzy projekcji
    projection = genProjection(fNear, fFar, fAspectRatio, fFovRad);

    // Deklaracja macierzy rotacji
    matrix4x4 MatrixRotX, MatrixRotZ;

    // Ustalanie kąta rotacji zmieniającego się w czasie (zależnego od ctr)
    float angle = 1.0f + ctr * 0.001;

    // Generowanie macierzy rotacji wzdłuż osi X i Z
    MatrixRotX = genRotationX(angle);
    MatrixRotZ = genRotationZ(angle);

    // Iteracja przez wszystkie trójkąty w siatce sześcianu
    for (auto &tri: meshCube.triangles) {
        // Deklaracja różnych wersji trójkąta (przekształconego, zrotowanego, przesuniętego itp.)
        triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

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
        triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
        triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
        triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

        // create normal to triangle
        vec3 normal = normalVec(triTranslated);

        if (dotProduct(normal, triTranslated.p[0] - cameraPos) < 0.0f) {
            // Ilumination
            float length = lightSource.calLength();
            lightSource.x /= length;
            lightSource.y /= length;
            lightSource.z /= length;

            float dp = dotProduct(normal, lightSource);

            RGB color = generateRGB(dp);

            // Projekcja trójkąta 3D na płaszczyznę 2D
            triProjected.p[0] = multiplyMatrixVector(triTranslated.p[0], projection);
            triProjected.p[1] = multiplyMatrixVector(triTranslated.p[1], projection);
            triProjected.p[2] = multiplyMatrixVector(triTranslated.p[2], projection);

            // Dodanie przesunięcia w osi X i Y, aby trójkąt znalazł się w widocznym zakresie
            float offset = 0.75f;
            triProjected.p[0].x += offset;
            triProjected.p[0].y += offset;
            triProjected.p[1].x += offset;
            triProjected.p[1].y += offset;
            triProjected.p[2].x += offset;
            triProjected.p[2].y += offset;

            // Skalowanie trójkąta na podstawie rozmiarów okna
            float scale = 0.7f;
            triProjected.p[0].x *= scale * (float) windowWidth;
            triProjected.p[0].y *= scale * (float) windowHeight;
            triProjected.p[1].x *= scale * (float) windowWidth;
            triProjected.p[1].y *= scale * (float) windowHeight;
            triProjected.p[2].x *= scale * (float) windowWidth;
            triProjected.p[2].y *= scale * (float) windowHeight;

            // Rysowanie trójkąta na ekranie za pomocą SFML
            sfml.fillTriangle(
                triProjected.p[0].x, triProjected.p[0].y,
                triProjected.p[1].x, triProjected.p[1].y,
                triProjected.p[2].x, triProjected.p[2].y,color
            );
        }
    }

    // Obsługa zdarzeń SFML
    sfml.handleEvents();

    // Aktualizacja ekranu po renderowaniu
    sfml.updateScreen();
}
