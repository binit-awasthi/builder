#include "core/EventHandler.hpp"

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

void EventHandler::handleMouseMoveEvents(sf::Event event)
{
}

void EventHandler::handleKeyPressEvents(sf::Event event)
{
    if (event.key.control && event.key.code == sf::Keyboard::Q)
    {
        sim::closeWindow(window);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        sim::fileOpener();
}

void EventHandler::handleKeyReleaseEvents(sf::Event event)
{
}

void EventHandler::handleMousePressEvents(const sf::Event &event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        isDragging = true;
        start = sim::snapToGrid({event.mouseButton.x, event.mouseButton.y});
        wire = std::make_shared<Wire>();
        wire->addPoint(start);

        DrawHandler::itemToDraw = wire;
    }
    if (event.mouseButton.button == sf::Mouse::Right)
    {
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
                Wire::addWire(wire);
            }
        }
    }
}
