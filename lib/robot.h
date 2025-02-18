#ifndef ROBOT_H
#define ROBOT_H

#include "render.h"
#include <thread>
#include <chrono>

class robot {
    int screenWidth = 1500, screenHeight = 1500;

    mesh arm_1, arm_2, arm_3, base, elbow, shoulder, wrist;

    render renderRobot;

    SFMLhandler sfml;

public:
    robot();
    void run();
};


#endif //ROBOT_H
