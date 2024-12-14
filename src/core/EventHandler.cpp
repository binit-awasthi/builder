#include "core/EventHandler.hpp"

std::unique_ptr<Wire> EventHandler::wire = nullptr;

EventHandler::EventHandler(sf::RenderWindow &window) : window(window)
{
    isDragging = false;
}

void EventHandler::handleEvents(sf::Event event)
{
    if (event.type == sf::Event::Closed)
    {
        sim::closeWindow(window);
    }
    if (event.type == sf::Event::KeyPressed)
        handleKeyPressEvents(event);
    if (event.type == sf::Event::MouseButtonPressed)
        handleMousePressEvents(event);
    if (event.type == sf::Event::MouseButtonReleased)
        handleMouseReleaseEvents(event);
}

void EventHandler::handleMouseMoveEvents(const sf::Event &event)
{
}

void EventHandler::handleKeyPressEvents(const sf::Event &event)
{
    if (event.key.control && event.key.code == sf::Keyboard::Q)
    {
        sim::closeWindow(window);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        sim::fileOpener();
}

void EventHandler::handleKeyReleaseEvents(const sf::Event &event)
{
}

void EventHandler::handleMousePressEvents(const sf::Event &event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        isDragging = true;
        start = sim::snapToGrid({event.mouseButton.x, event.mouseButton.y});
        wire = std::make_unique<Wire>();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            Node::addNode(std::make_unique<Node>(Node::Operation::NAND, sim::snapToGrid({event.mouseButton.x, event.mouseButton.y})));
        }

        bool validSource = false;

        for (auto &node : Node::nodes)
        {
            for (int i = 0; i < node->oPins.size(); i++)
            {
                if (node->oPins[i].contains(sim::getMousePos(window)))
                {
                    wire->addPoint(start);
                    wire->source = node;
                    wire->outputIndex = i;
                    validSource = true;
                    break;
                }
            }
            if (validSource)
                break;
        }

        if (!validSource)
        {
            wire.reset();
        }
    }

    if (event.mouseButton.button == sf::Mouse::Right)
    {
        sf::Vector2f mousePos = sim::getMousePos(window);

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
        isDragging = false;
        if (wire)
        {
            bool validDestination = false;

            for (auto &node : Node::nodes)
            {
                for (int i = 0; i < node->iPins.size(); i++)
                {
                    if (node->iPins[i].contains(sim::getMousePos(window)))
                    {
                        wire->addPoint(sim::snapToGrid(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
                        wire->destination = node;
                        wire->inputIndex = i;
                        validDestination = true;
                        break;
                    }
                }
                if (validDestination)
                    break;
            }

            if (!validDestination || wire->outputIndex == -1 || wire->inputIndex == -1)
            {
                wire.reset();
            }
            else
            {
                Wire::addWire(std::move(wire));
            }
        }
    }
}
