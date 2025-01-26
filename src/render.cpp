#include "render.h"

render::render() : sfml(windowWidth, windowHeight, "3D rendering") {
    meshCube.generateCube();
    fAspectRatio = static_cast<float>(windowHeight) / windowWidth;
    fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
}

void render::render2Dview() {
    ctr ++;
    sfml.clearScreen({200, 200, 200});
    projection = genProjection(fNear, fFar, fAspectRatio, fFovRad);
    matrix4x4 MatrixRotX, MatrixRotZ;
    float angle = 1.0f + ctr*0.1;
    MatrixRotX = genRotationX(angle);
    MatrixRotZ = genRotationZ(angle);


    for (auto &tri: meshCube.triangles) {
        triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

        triRotatedZ.p[0] = multiplyMatrixVector(tri.p[0], MatrixRotZ);
        triRotatedZ.p[1] = multiplyMatrixVector(tri.p[1], MatrixRotZ);
        triRotatedZ.p[2] = multiplyMatrixVector(tri.p[2], MatrixRotZ);

        triRotatedZX.p[0] = multiplyMatrixVector(triRotatedZ.p[0], MatrixRotX);
        triRotatedZX.p[1] = multiplyMatrixVector(triRotatedZ.p[1], MatrixRotX);
        triRotatedZX.p[2] = multiplyMatrixVector(triRotatedZ.p[2], MatrixRotX);

        triTranslated = triRotatedZX;
        triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
        triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
        triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

        triProjected.p[0] = multiplyMatrixVector(triTranslated.p[0], projection);
        triProjected.p[1] = multiplyMatrixVector(triTranslated.p[1], projection);
        triProjected.p[2] = multiplyMatrixVector(triTranslated.p[2], projection);

        float offset = 1.0f;
        triProjected.p[0].x += offset;
        triProjected.p[0].y += offset;
        triProjected.p[1].x += offset;
        triProjected.p[1].y += offset;
        triProjected.p[2].x += offset;
        triProjected.p[2].y += offset;

        float scale = 0.5f;
        triProjected.p[0].x *= scale * (float) windowWidth;
        triProjected.p[0].y *= scale * (float) windowHeight;
        triProjected.p[1].x *= scale * (float) windowWidth;
        triProjected.p[1].y *= scale * (float) windowHeight;
        triProjected.p[2].x *= scale * (float) windowWidth;
        triProjected.p[2].y *= scale * (float) windowHeight;


        sfml.drawTriangle(triProjected.p[0].x, triProjected.p[0].y,
                          triProjected.p[1].x, triProjected.p[1].y,
                          triProjected.p[2].x, triProjected.p[2].y
                          , {0, 0, 0}, 3.0f);

        // std::cout << "time: " << ctr << " p0: " << triProjected.p[0].x << "x" << triProjected.p[0].y << " p1: " <<
        //         triProjected.p[1].x << "x"
        //         << triProjected.p[1].y << " p2: " << triProjected.p[2].x << "x" << triProjected.p[2].y << std::endl;
    }

    sfml.handleEvents();
    sfml.updateScreen();
}
