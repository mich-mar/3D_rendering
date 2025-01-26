#ifndef RENDER_H
#define RENDER_H

#include "headers.h"
#include "math.h"
#include "matrix4x4.h"
#include "SFMLhandler.h"

class render {
    mesh meshCube;
    mesh meshObject;
    matrix4x4 projection;
    float windowHeight = 1000, windowWidth = 1000;
    int ctr = 0;

    vec3 cameraPos;
    vec3 lightSource = {0.0f, 0.0f, -1.0f};

    SFMLhandler sfml;

    float fNear = 1.0f;
    float fFar = 100.0f;
    float fFov = 90.0f;
    float fAspectRatio;
    float fFovRad;

public:
    render();
    render(float windowHeight, float windowWidth);
    void render2Dview();
};

#endif //RENDER_H
