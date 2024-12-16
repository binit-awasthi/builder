#include "core/EventHandler.hpp"

std::unique_ptr<Wire> EventHandler::wire = nullptr;

EventHandler::EventHandler(sf::RenderWindow &window) : window(window), isDragging(false), selectedNode(nullptr) {}

void EventHandler::handleEvents(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        sim::closeWindow(window);
        break;

    case sf::Event::KeyPressed:
        handleKeyPressEvents(event);
        break;

    case sf::Event::MouseButtonPressed:
        handleMousePressEvents(event);
        break;

    case sf::Event::MouseButtonReleased:
        handleMouseReleaseEvents(event);
        break;

    case sf::Event::MouseMoved:
        handleMouseMoveEvents(event);
        break;

    default:
        break;
    }
}

void EventHandler::handleKeyPressEvents(const sf::Event &event)
{
    if (event.key.control)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Q:
            sim::closeWindow(window);
            break;
        case sf::Keyboard::O:
            sim::fileOpener();
            break;
        default:
            break;
        }
    }
}

void EventHandler::handleMousePressEvents(const sf::Event &event)
{
    auto mousePos = sim::getMousePos(window);
    auto snappedPos = sim::snapToGrid(static_cast<sf::Vector2i>(mousePos));

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        handleLeftMousePress(mousePos, snappedPos);
    }
    else if (event.mouseButton.button == sf::Mouse::Right)
    {
        handleRightMousePress(mousePos);
    }
}

void EventHandler::handleLeftMousePress(const sf::Vector2f &mousePos, const sf::Vector2i &snappedPos)
{
    isDragging = true;
    wire = std::make_unique<Wire>();
    start = snappedPos;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
    {
        Node::addNode(std::make_unique<Node>(Node::Operation::NOR, snappedPos));
        selectedNode = Node::nodes.back().get();
        nodeInitialPosition = mousePos;
        return;
    }

    if (checkHoverOutput(mousePos))
        return;

    Wire *hoveredWire = Wire::checkHovered(mousePos);
    if (hoveredWire)
    {
        this->wire->addPoint(start);
        this->wire->source = hoveredWire->source;
        this->wire->outputIndex = hoveredWire->outputIndex;
        return;
    }

    wire.reset();
}

void EventHandler::handleRightMousePress(const sf::Vector2f &mousePos)
{
    if (Wire::deleteHovered(mousePos))
        return;
    if (Node::deleteHovered(mousePos))
        return;
}

void EventHandler::handleMouseReleaseEvents(const sf::Event &event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = sim::getMousePos(window);
        auto snappedPos = sim::snapToGrid(static_cast<sf::Vector2i>(mousePos));
        isDragging = false;

        if (selectedNode)
        {
            selectedNode->setPosition(sim::snapToGrid(static_cast<sf::Vector2i>(selectedNode->getPosition())));
            selectedNode->hoverInactive();
            selectedNode = nullptr;
        }

        checkHoverInput(snappedPos);
    }
}

void EventHandler::handleMouseMoveEvents(const sf::Event &event)
{
    moveSelected();
}

bool EventHandler::checkHoverOutput(const sf::Vector2f &pos)
{
    for (auto &node : Node::nodes)
    {
        for (int i = 0; i < node->oPins.size(); i++)
        {
            if (node->oPins[i].contains(pos))
            {
                wire->addPoint(start);
                wire->source = node;
                wire->outputIndex = i;
                return true;
            }
        }

        if (node->contains(pos))
        {
            selectedNode = node.get();
            nodeInitialPosition = pos;
            return true;
        }
    }
    return false;
}

void EventHandler::moveSelected()
{
    if (selectedNode)
    {
        auto mousePos = sim::getMousePos(window);
        auto delta = mousePos - nodeInitialPosition;
        nodeInitialPosition = mousePos;

        selectedNode->move(delta);

        for (auto &wire : Wire::wires)
        {
            if (wire->source.get() == selectedNode || wire->destination.get() == selectedNode)
                wire->updatePosition();
        }
    }
}

void EventHandler::checkHoverInput(const sf::Vector2i &snappedPos)
{
    if (wire)
    {
        for (auto &node : Node::nodes)
        {
            for (int i = 0; i < node->iPins.size(); i++)
            {
                if (node->iPins[i].contains(sim::getMousePos(window)))
                {
                    wire->addPoint(snappedPos);
                    wire->destination = node;
                    wire->inputIndex = i;

                    if (wire->outputIndex != -1 && wire->inputIndex != -1)
                    {
                        Wire *prevWire = node->iPins[wire->inputIndex].wire;
                        if (prevWire)
                        {
                            Wire::deleteWire(prevWire);
                        }

                        node->iPins[wire->inputIndex].wire = wire.get();

                        Wire::addWire(std::move(wire));
                        return;
                    }
                }
            }
        }
        wire.reset();
    }
}