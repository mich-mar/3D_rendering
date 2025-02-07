#ifndef ROBOT_H
#define ROBOT_H

#include "render.h"

std::vector<std::string> files = {
    "Arm 1.obj", "Arm 2.obj", "Arm 3.obj", "Base.obj",
    "Elbow.obj", "Shoulder.obj", "Wrist.obj"
};

class robot {
    int screenWidth = 1500, screenHeight = 1500;

    std::vector<render> parts;

    public:
      robot();
};



#endif //ROBOT_H
