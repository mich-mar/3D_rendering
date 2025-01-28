#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <ctime>
#include <math3D.h>
#include <string>
#include "matrix4x4.h"
#include "SFMLhandler.h"
#include <algorithm>

class render {
    mesh meshObject;
    matrix4x4 projection;
    float windowHeight = 1000, windowWidth = 1000;
    int ctr = 0;

    // Deklaracja macierzy rotacji
    matrix4x4 MatrixRotX, MatrixRotZ;
    std::vector<triangle3D> trianglesToRaster;

    // Deklaracja różnych wersji trójkąta (przekształconego, zrotowanego, przesuniętego itp.)
    triangle3D triModified;

    float depthOffset = 5.0f;
    vec3D normal;
    float length;
    float dp;
    float Xoffset = 2.0f;
    float Yoffset = 2.0f;
    float objScale = 0.5f;
    float rotAngle = 1.0f;

    vec3D cameraPos = {0.0f, 0.0f, 0.0f};
    vec3D lightSource = {0.0f, 0.0f, -1.0};

    SFMLhandler sfml;

    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 90.0f;
    float fAspectRatio;
    float fFovRad;

public:
    render(float windowHeight, float windowWidth, const std::string &filename);

    void render2Dview();

    triangle3D rot(triangle3D &tri, matrix4x4 &matrixRot);

    triangle3D transXY(triangle3D &tri);

    triangle3D triScale(triangle3D& triProjected);

    triangle3D transformTriangle3D(const triangle3D& triTranslated, const matrix4x4& projection);
};

#endif //RENDER_H
