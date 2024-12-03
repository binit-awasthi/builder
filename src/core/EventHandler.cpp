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

void EventHandler::handleMousePressEvents(sf::Event event)
{

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        isDragging = true;
        start = sim::snapToGrid({event.mouseButton.x, event.mouseButton.y});
        wire = new Wire();
        wire->addPoint(start);

        DrawHandler::itemsToDraw.push_back(wire);
    }
}

void EventHandler::handleMouseReleaseEvents(sf::Event event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        isDragging = false;
        if (wire)
        {
            wire = nullptr;
        }
    }
}

void EventHandler::handleKeyPressEvents(sf::Event event)
{
    // std::cout << "event key code: " << event.key.code << std::endl;
    if (event.key.control && event.key.code == sf::Keyboard::Q)
    {
        sim::closeWindow(window);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        sim::fileOpener();
}

void EventHandler::handleKeyReleaseEvents(sf::Event event)
{
    // std::cout << "event key code: " << event.key.code << std::endl;
}
