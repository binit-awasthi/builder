#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <utils/tinyfiledialogs.hpp>

namespace sim
{
    void fileOpener();
    void closeWindow(sf::RenderWindow &window);
    sf::Vector2f getMousePos(sf::RenderWindow &);
    extern sf::Font font;
    extern sf::Image icon;
    void loadAssets();
    float distance(const sf::Vector2f &point1, const sf::Vector2f &point2);
    float getAngle(sf::Vector2f start, sf::Vector2f end);
}

#endif