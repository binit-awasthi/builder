#include "components/ElementalWire.hpp"

ElementalWire::ElementalWire(sf::Vector2f start, sf::Vector2f end) : start(start), end(end)
{
    thickness = 5.f;
    rect.setSize(sf::Vector2f(sim::distance(start, end), thickness));
    rect.setOrigin(0.f, thickness / 2);
    rect.setPosition(start);
    rect.setFillColor(sf::Color::Green);
}

void ElementalWire::setWidth(float width)
{
    rect.setSize(sf::Vector2f(sim::distance(start, end), thickness));
}

void ElementalWire::setEnd(sf::Vector2f newEnd)
{
    end = newEnd;
    rect.setRotation(sim::getAngle(start, end));
    rect.setSize(sf::Vector2f(sim::distance(start, end), thickness));
}

void ElementalWire::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect, states);
}