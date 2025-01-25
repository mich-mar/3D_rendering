#ifndef RENDER_H
#define RENDER_H

#include "headers.h"
#include "math.h"

class render {
    mesh meshCube, meshCubeTemplate;

public:
    render();
    void renderCubeTemplate();
};

#endif //RENDER_H
