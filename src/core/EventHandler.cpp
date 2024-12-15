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
    if (event.key.control && event.key.code == sf::Keyboard::Q)
        sim::closeWindow(window);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        sim::fileOpener();
}

void EventHandler::handleMousePressEvents(const sf::Event &event)
{
    auto mousePos = sim::getMousePos(window);
    auto snappedPos = sim::snapToGrid(static_cast<sf::Vector2i>(mousePos));

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        isDragging = true;
        wire = std::make_unique<Wire>();
        start = snappedPos;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        {
            Node::addNode(std::make_unique<Node>(Node::Operation::NAND, snappedPos));
            selectedNode = Node::nodes.back().get();
            nodeInitialPosition = mousePos;
            return;
        }

        for (auto &node : Node::nodes)
        {

            for (int i = 0; i < node->oPins.size(); i++)
            {
                if (node->oPins[i].contains(mousePos))
                {
                    wire->addPoint(start);
                    wire->source = node;
                    wire->outputIndex = i;
                    return;
                }
            }

            if (node->contains(mousePos))
            {
                selectedNode = node.get();
                nodeInitialPosition = mousePos;
                return;
            }
        }
        wire.reset();
    }
    else if (event.mouseButton.button == sf::Mouse::Right)
    {
        for (auto it = Wire::wires.begin(); it != Wire::wires.end(); ++it)
        {
            if ((*it)->contains(mousePos))
            {
                Wire::wires.erase(it);
                return;
            }
        }

        for (auto it = Node::nodes.begin(); it != Node::nodes.end(); ++it)
        {
            if ((*it)->contains(mousePos))
            {
                Node::nodes.erase(it);
                return;
            }
        }
    }
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
            selectedNode = nullptr;
        }

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
                            Wire::addWire(std::move(wire));
                            return;
                        }
                    }
                }
            }
            wire.reset();
        }
    }
}

void EventHandler::handleMouseMoveEvents(const sf::Event &event)
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
