#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils/utils.hpp"
#include "core/DrawHandler.hpp"
#include "components/Wire.hpp"
#include "components/Node.hpp"
#include "components/Pin.hpp"

class EventHandler
{
    sf::RenderWindow &window;
    void handleKeyPressEvents(const sf::Event &);
    void handleKeyReleaseEvents(const sf::Event &);
    void handleMouseMoveEvents(const sf::Event &);
    void handleMousePressEvents(const sf::Event &);
    void handleMouseReleaseEvents(const sf::Event &);

    sf::Vector2i start;
    bool checkHoverOutput(const sf::Vector2f &);
    void moveSelected();
    void checkHoverInput(const sf::Vector2i &);
    //
    void handleLeftMousePress(const sf::Vector2f &mousePos, const sf::Vector2i &snappedPos);
    void handleRightMousePress(const sf::Vector2f &mousePos);
    //
public:
    static std::unique_ptr<Wire> wire;
    bool isDragging;
    EventHandler(sf::RenderWindow &);
    void handleEvents(sf::Event);

    //
    Node *selectedNode;
    sf::Vector2f nodeInitialPosition;

    //
};

#endif