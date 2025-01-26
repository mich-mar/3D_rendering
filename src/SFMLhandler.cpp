#include "SFMLhandler.h"

// Constructor
SFMLhandler::SFMLhandler(float width, float height, const std::string& title)
    : windowHeight(height), windowWidth(width), window(sf::VideoMode(width, height), title) {}

// Draws an entire mesh (outline or filled)
void SFMLhandler::drawMesh(const mesh& m, const RGB& color, bool fill) {

}

// Clears the screen with a specified background color
void SFMLhandler::clearScreen(const RGB& backgroundColor) {
    window.clear(convertToSFMLColor(backgroundColor));
}

// Updates the screen
void SFMLhandler::updateScreen() {
    window.display();
}

// Converts RGB struct to sf::Color
sf::Color SFMLhandler::convertToSFMLColor(const RGB& color) {
    return sf::Color(color.r, color.g, color.b);
}

// Converts 3D point to screen coordinates (assuming z is ignored)
sf::Vector2f SFMLhandler::convertToScreenCoordinates(const vec3& point) {
    // Convert to 2D screen space (assumes a projection method is handled elsewhere)
    return sf::Vector2f(point.x * 400 + 400, -point.y * 300 + 300);
}

// Main loop
void SFMLhandler::run(const mesh& m) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        clearScreen({0, 0, 0}); // Black background
        drawMesh(m, {255, 255, 255}, true); // Draw filled mesh in white
        updateScreen();
    }
}

bool SFMLhandler::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            exit(0);
            return false; // Signal to stop the main loop
        }
    }
    return true; // Continue running
}

void SFMLhandler::drawTriangle(int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y, const RGB& color, float thickness) {
    // Helper function to create a line with thickness
    auto createThickLine = [&](float x1, float y1, float x2, float y2, float thickness, const sf::Color& sfColor) {
        sf::Vector2f direction(x2 - x1, y2 - y1);
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        sf::Vector2f normal(-direction.y, direction.x);

        sf::Vector2f offset = normal * thickness / 2.f;

        sf::ConvexShape line;
        line.setPointCount(4);
        line.setPoint(0, sf::Vector2f(x1, y1) + offset);
        line.setPoint(1, sf::Vector2f(x2, y2) + offset);
        line.setPoint(2, sf::Vector2f(x2, y2) - offset);
        line.setPoint(3, sf::Vector2f(x1, y1) - offset);
        line.setFillColor(sfColor);

        return line;
    };

    // Convert RGB to sf::Color
    sf::Color sfColor(color.r, color.g, color.b);

    // Draw the three edges of the triangle
    sf::ConvexShape edge1 = createThickLine(p1_x, p1_y, p2_x, p2_y, thickness, sfColor);
    sf::ConvexShape edge2 = createThickLine(p2_x, p2_y, p3_x, p3_y, thickness, sfColor);
    sf::ConvexShape edge3 = createThickLine(p3_x, p3_y, p1_x, p1_y, thickness, sfColor);

    window.draw(edge1);
    window.draw(edge2);
    window.draw(edge3);
}

sf::Int32 SFMLhandler::getElapsedTime() {
    elapsed = clock.restart();
    return elapsed.asMilliseconds(); // Zwróci liczbę milisekund jako sf::Int32
}




