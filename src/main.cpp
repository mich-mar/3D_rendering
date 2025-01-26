#include "SFMLhandler.h"
#include <vector>
#include <SFML/Graphics.hpp>

int main() {
    // Define a vector of points for a triangle
    std::vector<sf::Vector2f> triangle1 = {
        {400.0f, 150.0f}, // Top vertex
        {300.0f, 450.0f}, // Bottom-left vertex
        {500.0f, 450.0f}  // Bottom-right vertex
    };

    // Define another triangle
    std::vector<sf::Vector2f> triangle2 = {
        {200.0f, 100.0f},  // Top vertex
        {100.0f, 400.0f},  // Bottom-left vertex
        {300.0f, 400.0f}   // Bottom-right vertex
    };

    // Initialize the SFML handler
    SFMLhandler handler(800, 600, "SFML Triangle Renderer");

    // Main rendering loop
    while (true) {
        // Process window events
        if (!handler.handleEvents()) {
            break; // Exit the loop if the window is closed
        }

        // Clear the screen with a black background
        handler.clearScreen({200, 200, 200});

        // Draw the first triangle as an outline (red, thickness = 2)
        handler.drawPolygon(triangle1, {0, 0, 0}, 5.0f);

        // Draw the second triangle as a filled shape (green)
        handler.drawFilledPolygon(triangle2, {0, 0, 0});

        // Update the screen
        handler.updateScreen();
    }

    return 0;
}
