#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "utils/utils.hpp"
#include "core/DrawHandler.hpp"
// #include "components/Wire.hpp"
#include "components/ElementalWire.hpp"

class EventHandler
{
    sf::RenderWindow &window;
    void handleMousePressEvents(sf::Event);
    void handleMouseReleaseEvents(sf::Event);
    void handleKeyPressEvents(sf::Event);
    void handleKeyReleaseEvents(sf::Event);
    void handleMouseMoveEvents(sf::Event);
    ElementalWire *wire;
    bool mouseMoved = false;
    sf::Clock clock;

public:
    EventHandler(sf::RenderWindow &);
    void handleEvents(sf::Event);
};

#endif