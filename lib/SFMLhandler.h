#ifndef SFMLHANDLER_H
#define SFMLHANDLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>

class SFMLhandler {
private:
    sf::RenderWindow window;

public:
    // Konstruktor klasy
    SFMLhandler();

    void run();

};

#endif //SFMLHANDLER_H
