#ifndef SFMLHANDLER_H
#define SFMLHANDLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include <math.h>

struct RGB {
    int r;
    int g;
    int b;
};

class SFMLhandler {
    sf::RenderWindow window;

public:
    SFMLhandler(int width, int height, const std::string& title);
    void drawTriangle(const triangle& tri, const RGB& color, float thickness);
    void drawFilledTriangle(const triangle& tri, const RGB& color);
    void drawMesh(const mesh& m, const RGB& color, bool fill);
    void clearScreen(const RGB& backgroundColor);
    void updateScreen();
    sf::Color convertToSFMLColor(const RGB& color);
    sf::Vector2f convertToScreenCoordinates(const vec3& point);
    void run(const mesh& m);
    void drawPolygon(const std::vector<sf::Vector2f>& points, RGB color, float thickness);
    void drawFilledPolygon(const std::vector<sf::Vector2f>& points, RGB color);
    bool handleEvents();
};

#endif //SFMLHANDLER_H
