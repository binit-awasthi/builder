#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils/utils.hpp"
#include "core/DrawHandler.hpp"
#include "components/Wire.hpp"
#include "components/Node.hpp"
#include "components/Pin.hpp"
#include "components/Input.hpp"
#include "components/Output.hpp"

class EventHandler
{
    sf::RenderWindow &window;
    sf::Vector2i start;

    void handleKeyPressEvents(const sf::Event &);
    void handleMouseMoveEvents(const sf::Event &);
    void handleMousePressEvents(const sf::Event &);
    void handleMouseReleaseEvents(const sf::Event &);
    void moveSelected();
    void checkHoverInput(const sf::Vector2i &);
    void handleLeftMousePress(const sf::Vector2f &mousePos, const sf::Vector2i &snappedPos);
    void handleRightMousePress(const sf::Vector2f &mousePos);
    bool checkHoverOutput(const sf::Vector2f &);
    //
    std::vector<Node *> selectedNodes;
    std::vector<Wire *> selectedWires;
    std::vector<Pin *> selectedPins;
    std::vector<Output *> selectedOutputs;
    std::vector<Input *> selectedInputs;

public:
    bool isDragging;
    Node *selectedNode;
    sf::Vector2f initialPos;

    static std::unique_ptr<Wire> wire;

    void handleEvents(sf::Event);

    EventHandler(sf::RenderWindow &);
};

#endif