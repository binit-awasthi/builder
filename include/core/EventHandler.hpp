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
    void handleKeyPressEvents(sf::Event);
    void handleKeyReleaseEvents(sf::Event);
    void handleMouseMoveEvents(sf::Event);

    //
    void handleMousePressEvents(const sf::Event &event);
    void handleMouseReleaseEvents(const sf::Event &event);
    //

    sf::Vector2i start;

public:
    std::shared_ptr<Wire> wire = nullptr;
    bool isDragging;
    EventHandler(sf::RenderWindow &);
    void handleEvents(sf::Event);
};

#endif