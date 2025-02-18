#ifndef SFMLHANDLER_H
#define SFMLHANDLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include <mesh.h>
#include <vec3D.h>
#include "RGB.h"
#include "point2D.h"

struct SFMLhandler {
    sf::RenderWindow window;
    float windowWidth, windowHeight;
    sf::Time elapsed;
    sf::Clock clock;

public:
    SFMLhandler(float width, float height, std::string title);

    void drawTriangle(point2D p1, point2D p2, point2D p3, const RGB &color, float thickness);

    void fillTriangle(point2D p1, point2D p2, point2D p3, const RGB &color);

    void clearScreen(const RGB &backgroundColor);

    void updateScreen();

    sf::ConvexShape createThickLine (float x1, float y1, float x2, float y2, float thickness, const sf::Color &sfColor);

    sf::Color convertToSFMLColor(const RGB &color);

    bool handleEvents();

    sf::Int32 getElapsedTime();

    void renderTriangles(std::vector<triangle3D>& triangles);
};

RGB generateRGB(float illumination);

#endif //SFMLHANDLER_H