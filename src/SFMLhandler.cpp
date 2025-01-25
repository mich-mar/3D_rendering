
#include "SFMLhandler.h"

#include "SFMLhandler.h"

// Konstruktor
SFMLhandler::SFMLhandler() : window(sf::VideoMode(512, 512), "SFML Tutorial", sf::Style::Close | sf::Style::Resize) {
}

void SFMLhandler::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
}
