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
    matrix4x4 MatrixRotX, MatrixRotZ, MatrixRotY;
    std::vector<triangle3D> trianglesToRaster;

    // Deklaracja różnych wersji trójkąta (przekształconego, zrotowanego, przesuniętego itp.)
    triangle3D triModified;

    float depthOffset = 200.0f;
    vec3D normal;
    float length;
    float dp;
    float Xoffset = 2.0f;
    float Yoffset = 2.0f;
    float objScale = 3.0f;
    float rotAngle = 10.0f;

    vec3D cameraPos = {0.0f, 0.0f, 0.0f};
    vec3D lightSource = {0.0f, 0.0f, -1.0};

    SFMLhandler sfml;

    float fNear = 0.1f;
    float fFar = 100.0f;
    float fFov = 90.0f;
    float fAspectRatio;
    float fFovRad;

public:

    render(float windowHeight, float windowWidth, const std::string &filename);

    void setParam(float fNear, float fFar, float fFov);

    void setOffsets(float Xoffset, float Yoffset, float depthOffset);

    void setScale(float objScale);

    std::vector<triangle3D> render2Dview(float angX, float angY, float angZ, mesh& meshObject);

    void render2Dview(float angX, float angY, float angZ);

    triangle3D rot(triangle3D &tri, matrix4x4 &matrixRot);

    triangle3D transXY(triangle3D &tri);

    triangle3D triScale(triangle3D &triProjected);

    triangle3D transformTriangle3D(const triangle3D &triTranslated, const matrix4x4 &projection);

    // todo: check if it works
    render(render&& other) noexcept = default;
    render& operator=(render&& other) noexcept = default;

};

#endif //RENDER_H