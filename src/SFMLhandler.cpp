#include "SFMLhandler.h"

// Constructor
SFMLhandler::SFMLhandler(float width, float height, std::string title)
    : windowHeight(height), windowWidth(width), window(sf::VideoMode(width, height), title) {
}




// Clears the screen with a specified background color
void SFMLhandler::clearScreen(const RGB &backgroundColor) {
    window.clear(convertToSFMLColor(backgroundColor));
}

// Updates the screen
void SFMLhandler::updateScreen() {
    window.display();
}

// Converts RGB struct to sf::Color
sf::Color SFMLhandler::convertToSFMLColor(const RGB &color) {
    return sf::Color(color.r, color.g, color.b);
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

// Helper function to create a line with thickness
sf::ConvexShape SFMLhandler::createThickLine(float x1, float y1, float x2, float y2, float thickness,
                                             const sf::Color &sfColor) {
    sf::Vector2f direction(x2 - x1, y2 - y1);
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
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

void SFMLhandler::drawTriangle(point2D p1, point2D p2, point2D p3, const RGB &color,
                               float thickness) {
    // Convert RGB to sf::Color
    sf::Color sfColor(color.r, color.g, color.b);

    // Draw the three edges of the triangle
    sf::ConvexShape edge1 = createThickLine(p1.x, p1.y, p2.x, p2.y, thickness, sfColor);
    sf::ConvexShape edge2 = createThickLine(p2.x, p2.y, p3.x, p3.y, thickness, sfColor);
    sf::ConvexShape edge3 = createThickLine(p3.x, p3.y, p1.x, p1.y, thickness, sfColor);

    window.draw(edge1);
    window.draw(edge2);
    window.draw(edge3);
}

sf::Int32 SFMLhandler::getElapsedTime() {
    elapsed = clock.restart();
    return elapsed.asMilliseconds(); // Zwróci liczbę milisekund jako sf::Int32
}

void SFMLhandler::fillTriangle(point2D p1, point2D p2, point2D p3, const RGB &color) {
    // Create a triangle using sf::VertexArray
    sf::VertexArray triangle(sf::Triangles, 3);

    // Convert RGB to sf::Color
    sf::Color sfColor(color.r, color.g, color.b);

    // Set the vertices positions and colors
    triangle[0].position = sf::Vector2f(p1.x, p1.y);
    triangle[0].color = sfColor;

    triangle[1].position = sf::Vector2f(p2.x, p2.y);
    triangle[1].color = sfColor;

    triangle[2].position = sf::Vector2f(p3.x, p3.y);
    triangle[2].color = sfColor;

    // Draw the triangle to the window
    window.draw(triangle);
}

RGB generateRGB(float illumination) {
    // Clamp the illumination value between 0 and 1
    if (illumination < 0.0f) illumination = 0.0f;
    if (illumination > 1.0f) illumination = 1.0f;

    // Calculate the intensity based on illumination
    int intensity = static_cast<int>(illumination * 255) / 2 + 127;
    return {intensity, intensity, intensity};
}