//
// Created by michal on 06.02.25.
//

#include "robot.h"

robot::robot() : renderRobot(1500, 1500, "Arm 1.obj"), sfml(1500, 1500, "robot") {
    std::vector<std::string> objNames = {
        "Arm 1.obj", "Arm 2.obj", "Arm 3.obj", "Base.obj",
        "Elbow.obj", "Shoulder.obj", "Wrist.obj"
    };

    arm_1.loadObj(objNames.at(0));
    arm_2.loadObj(objNames.at(1));
    arm_3.loadObj(objNames.at(2));
    base.loadObj(objNames.at(3));
    elbow.loadObj(objNames.at(4));
    shoulder.loadObj(objNames.at(5));
    wrist.loadObj(objNames.at(6));
}

void robot::run() {
    int a = 0;

    renderRobot.setOffsets(1.5, 1.5, 8);
    renderRobot.setParam(0.1, 100, 90);

    renderRobot.setScale(1.5);

    float angleX = M_PI / 2, angleY = 0, angleZ = M_PI / 2;

    std::vector<triangle3D> triangles, temp;

    while (true) {
        triangles.clear();

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, base);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, arm_1);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, arm_2);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, arm_3);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, shoulder);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, wrist);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        sfml.renderTriangles(triangles);

        angleX += 0.1;
        angleZ += 0.1;
    }
}
