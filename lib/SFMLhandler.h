#ifndef SFMLHANDLER_H
#define SFMLHANDLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include <mesh.h>
#include <vec4.h>

struct RGB {
    int r;
    int g;
    int b;
};

struct SFMLhandler {
    sf::RenderWindow window;
    float windowWidth, windowHeight;
    sf::Time elapsed;
    sf::Clock clock;

public:
    SFMLhandler(float width, float height, const std::string& title);
    void drawTriangle(int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y, const RGB& color, float thickness);
    void drawMesh(const mesh& m, const RGB& color, bool fill);
    void clearScreen(const RGB& backgroundColor);
    void updateScreen();
    sf::Color convertToSFMLColor(const RGB& color);
    sf::Vector2f convertToScreenCoordinates(const vec3& point);
    void run(const mesh& m);
    bool handleEvents();
    sf::Int32 getElapsedTime();
};

#endif //SFMLHANDLER_H
