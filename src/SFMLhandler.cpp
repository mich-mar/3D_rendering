#include "SFMLhandler.h"

// Constructor
SFMLhandler::SFMLhandler(int width, int height, const std::string& title)
    : window(sf::VideoMode(width, height), title) {}

// Draws an outline of a triangle
void SFMLhandler::drawTriangle(const triangle& tri, const RGB& color, float thickness) {
    sf::VertexArray lines(sf::LineStrip, 4);

    for (int i = 0; i < 3; i++) {
        lines[i].position = convertToScreenCoordinates(tri.p[i]);
        lines[i].color = convertToSFMLColor(color);
    }
    lines[3].position = lines[0].position; // Close the triangle
    lines[3].color = lines[0].color;

    window.draw(lines);
}

// Draws a filled triangle
void SFMLhandler::drawFilledTriangle(const triangle& tri, const RGB& color) {
    sf::ConvexShape shape;
    shape.setPointCount(3);
    shape.setFillColor(convertToSFMLColor(color));

    for (int i = 0; i < 3; i++) {
        shape.setPoint(i, convertToScreenCoordinates(tri.p[i]));
    }

    window.draw(shape);
}

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

void SFMLhandler::drawPolygon(const std::vector<sf::Vector2f>& points, RGB color, float thickness) {
    if (points.size() < 2) {
        return; // Need at least two points to draw
    }

    sf::Color sfColor(color.r, color.g, color.b);

    for (size_t i = 0; i < points.size(); ++i) {
        // Get the current point and the next point (wrapping around for the last segment)
        sf::Vector2f start = points[i];
        sf::Vector2f end = points[(i + 1) % points.size()];

        // Compute the direction vector and its perpendicular
        sf::Vector2f direction = end - start;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f unitDirection = direction / length;
        sf::Vector2f perpendicular(-unitDirection.y, unitDirection.x);

        // Compute the four corners of the thick line
        sf::Vector2f offset = perpendicular * (thickness / 2.0f);
        sf::Vector2f p1 = start + offset;
        sf::Vector2f p2 = start - offset;
        sf::Vector2f p3 = end - offset;
        sf::Vector2f p4 = end + offset;

        // Create a quad for this segment
        sf::Vertex quad[] = {
            sf::Vertex(p1, sfColor),
            sf::Vertex(p2, sfColor),
            sf::Vertex(p3, sfColor),
            sf::Vertex(p4, sfColor)
        };

        // Draw the quad
        window.draw(quad, 4, sf::Quads);
    }
}


void SFMLhandler::drawFilledPolygon(const std::vector<sf::Vector2f>& points, RGB color) {
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());
    polygon.setFillColor(sf::Color(color.r, color.g, color.b));

    for (size_t i = 0; i < points.size(); ++i) {
        polygon.setPoint(i, points[i]);
    }

    window.draw(polygon);
}

bool SFMLhandler::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return false; // Signal to stop the main loop
        }
    }
    return true; // Continue running
}

