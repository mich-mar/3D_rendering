#ifndef RENDER_H
#define RENDER_H

#include "headers.h"
#include "math.h"
#include "matrix4x4.h"
#include "SFMLhandler.h"
#include <algorithm>

class render {
    mesh meshObject;
    matrix4x4 projection;
    float windowHeight = 1000, windowWidth = 1000;
    int ctr = 0;

    vec3 cameraPos;
    vec3 lightSource = {0.0f, 0.0f, -1.0f};

    SFMLhandler sfml;

    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 90.0f;
    float fAspectRatio;
    float fFovRad;

public:
    render(float windowHeight, float windowWidth, std::string filename);

    void render2Dview();
};

#endif //RENDER_H
