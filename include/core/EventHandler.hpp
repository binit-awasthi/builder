#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "utils/utils.hpp"
#include "core/DrawHandler.hpp"
#include "components/Wire.hpp"

class EventHandler
{
    sf::RenderWindow &window;
    void handleMousePressEvents(sf::Event);
    void handleMouseReleaseEvents(sf::Event);
    void handleKeyPressEvents(sf::Event);
    void handleKeyReleaseEvents(sf::Event);
    void handleMouseMoveEvents(sf::Event);

    sf::Clock clock;
    sf::Vector2i start;

public:
    Wire *wire;
    bool isDragging;
    EventHandler(sf::RenderWindow &);
    void handleEvents(sf::Event);
};

#endif