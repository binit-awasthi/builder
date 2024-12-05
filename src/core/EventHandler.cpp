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
        wire->addPoint(start);

        DrawHandler::itemsToDraw.push_back(std::make_shared<Node>(sim::snapToGrid({event.mouseButton.x, event.mouseButton.y})));
        // DrawHandler::itemToDraw = wire;
    }
    if (event.mouseButton.button == sf::Mouse::Right)
    {
        wire.reset();
        Wire::deleteWire();
    }
}

void EventHandler::handleMouseReleaseEvents(const sf::Event &event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        isDragging = false;
        if (wire)
        {
            if (wire->getVertexCount() < 4)
            {
                wire.reset();
            }
            else
            {
                Wire::addWire(std::move(wire));
                wire.reset();
            }
        }
    }
}
