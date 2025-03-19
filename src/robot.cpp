//
// Created by michal on 06.02.25.
//

#include "robot.h"

robot::robot() : renderRobot(1500, 1500, "Arm 1.obj"), sfml(1500, 1500, "robot") {
    std::vector<std::string> objNames = {
        "base_v2.obj", "link_1_v2.obj", "link_2_v2.obj", "link_3_v2.obj", "link_4_v2.obj", "link_5_v2.obj",
        "accuator_v2.obj"
    };

    base.loadObj(objNames.at(0));
    accuator.loadObj(objNames.at(1));
    link_1.loadObj(objNames.at(2));
    link_2.loadObj(objNames.at(3));
    link_3.loadObj(objNames.at(4));
    link_4.loadObj(objNames.at(5));
    link_5.loadObj(objNames.at(6));
}

void robot::run() {
    int a = 0;

    renderRobot.setOffsets(1.5, 1.5, 100);
    renderRobot.setParam(0.1, 100, 90);

    renderRobot.setScale(1);

    float angleX = M_PI, angleY = M_PI/2+M_PI/5, angleZ = M_PI/10;

    std::vector<triangle3D> triangles, temp;

    while (true) {
        triangles.clear();

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, base);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, link_1);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, link_2);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, link_3);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, link_4);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, link_5);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        temp = renderRobot.render2Dview(angleX, angleY, angleZ, accuator);
        triangles.insert(triangles.end(), temp.begin(), temp.end());

        std::sort(triangles.begin(), triangles.end(), [](triangle3D &t1, triangle3D &t2) {
            float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
            float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
            return z1 > z2;
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        sfml.renderTriangles(triangles);

        angleX += 0.001;
        angleZ += 0.001;
        // angleY_temp += 0.1;
    }
}
