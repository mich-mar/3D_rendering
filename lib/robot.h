#ifndef ROBOT_H
#define ROBOT_H

#include "render.h"
#include <thread>
#include <chrono>

class robot {
    int screenWidth = 1500, screenHeight = 1500;

    mesh accuator, base, link_1, link_2, link_3, link_4, link_5;

    render renderRobot;

    SFMLhandler sfml;

public:
    robot();
    void run();
};


#endif //ROBOT_H
