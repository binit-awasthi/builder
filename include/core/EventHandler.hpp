#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <iostream>
#include <vector>
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
private:
    sf::RenderWindow &window;
    sf::Vector2i start;

    sf::Vector2f initialPos;

    std::vector<std::shared_ptr<Node>> selectedNodes;
    std::vector<std::shared_ptr<Wire>> selectedWires;
    std::vector<std::shared_ptr<Pin>> selectedPins;
    std::vector<std::shared_ptr<Output>> selectedOutputs;
    std::vector<std::shared_ptr<Input>> selectedInputs;

    void handleKeyPressEvents(const sf::Event &);
    void handleMouseMoveEvents(const sf::Event &);
    void handleMousePressEvents(const sf::Event &);
    void handleMouseReleaseEvents(const sf::Event &);

    void handleLeftMousePress(const sf::Vector2f &mousePos, const sf::Vector2i &snappedPos);
    void handleRightMousePress(const sf::Vector2f &mousePos);

    void checkHoverInput(const sf::Vector2i &snappedPos);
    bool checkHoverOutput(const sf::Vector2f &mousePos);

    void moveSelected();
    void resetSelections();

public:
    EventHandler(sf::RenderWindow &window);

    void handleEvents(const sf::Event &event);
    static std::shared_ptr<Wire> wire;
    Node *selectedNode;
    bool isDragging;
};

#endif
