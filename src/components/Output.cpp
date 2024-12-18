#include "components/Output.hpp"

std::vector<std::unique_ptr<Output>> Output::outputs;

Output::Output()
{
    setPosition();
}

void Output::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Indicator::draw(target, states);
    target.draw(pin);
}

void Output::setPosition(const sf::Vector2i &pos)
{
    Indicator::setPosition(pos);

    sf::FloatRect containerBounds = container.getLocalBounds();
    pin.shape.setPosition(pos.x - containerBounds.width / 2, pos.y);
}