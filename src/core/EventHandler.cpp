#include "core/EventHandler.hpp"

EventHandler::EventHandler(sf::RenderWindow &window) : window(window)
{
}

void EventHandler::handleEvents(sf::Event event)
{
    if (event.type == sf::Event::Closed)
    {
        sim::closeWindow(window);
    }
    if (event.type == sf::Event::KeyPressed)
        handleKeyPressEvents(event);
    if (event.type == sf::Event::KeyReleased)
        handleKeyReleaseEvents(event);
    if (event.type == sf::Event::MouseButtonPressed)
        handleMousePressEvents(event);
    if (event.type == sf::Event::MouseMoved)
        handleMouseMoveEvents(event);
    if (event.type == sf::Event::MouseButtonReleased)
        handleMouseReleaseEvents(event);
}

void EventHandler::handleMouseMoveEvents(sf::Event event)
{
    mouseMoved = true;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        if (wire)
        {
            wire->setEnd(sim::getMousePos(window));
        }
}

void EventHandler::handleMousePressEvents(sf::Event event)
{
    sf::Vector2f mousePos = sim::getMousePos(window);

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        // if (mouseMoved)
        {
            wire = new ElementalWire(mousePos, mousePos);
            DrawHandler::itemsToDraw.push_back(wire);
            std::cout << "wire created" << std::endl;
        }
    }
}

void EventHandler::handleMouseReleaseEvents(sf::Event event)
{
    // mouseMoved = false;
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        if (wire)
        {
            // wire->setEnd(sim::getMousePos(window));
            wire = nullptr;
        }
    }
}

void EventHandler::handleKeyPressEvents(sf::Event event)
{
    std::cout << "event key code: " << event.key.code << std::endl;
    if (event.key.control && event.key.code == sf::Keyboard::Q)
    {
        sim::closeWindow(window);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        sim::fileOpener();
}

void EventHandler::handleKeyReleaseEvents(sf::Event event)
{
    std::cout << "event key code: " << event.key.code << std::endl;
}