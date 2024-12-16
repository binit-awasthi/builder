#include "components/Pin.hpp"

Pin::Pin(bool state) : state(state)
{
    shape.setFillColor(getColor(style::color::low));
    shape.setRadius(sim::CELL_SIZE / 2);
    float radius = shape.getRadius();
    shape.setOrigin(radius, radius);
    shape.setOutlineColor(getColor(style::color::selected));
}

void Pin::setState(bool state)
{
    this->state = state;
    if (state)
        shape.setFillColor(getColor(style::color::high));
    else
        shape.setFillColor(getColor(style::color::low));
}

bool Pin::getState()
{
    return state;
}

void Pin::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape);
}

bool Pin::contains(sf::Vector2f point) const
{
    return shape.getGlobalBounds().contains(point);
}
sf::Vector2i Pin::getPosition()
{
    return static_cast<sf::Vector2i>(shape.getPosition());
}

void Pin::hoverActive()
{
    shape.setOutlineThickness(1.5f);
}
void Pin::hoverInactive()
{
    shape.setOutlineThickness(0.f);
}
