#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <utils/tinyfiledialogs.hpp>

namespace sim
{
    extern const int CELL_SIZE;
    extern const float WIRE_THICKNESS;
    extern sf::Font font;
    extern sf::Image icon;

    void fileOpener();
    void closeWindow(sf::RenderWindow &window);
    sf::Vector2f getMousePos(sf::RenderWindow &);
    void loadAssets();
    float distance(const sf::Vector2f &point1, const sf::Vector2f &point2);
    float getAngle(sf::Vector2f start, sf::Vector2f end);
    enum Direction
    {
        None,
        Horizontal,
        Vertical
    };
    Direction getDirection(const sf::Vector2f &start, const sf::Vector2f &end);
    sf::Vector2i snapToGrid(const sf::Vector2i &);
    void drawGrid(sf::RenderWindow &);

}

namespace style
{
    enum class color
    {
        wire,
        wireStart,
        gate,
        pin,
        window
    };
}

sf::Color getColor(style::color);
#endif
