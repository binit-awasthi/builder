#include "components/Output.hpp"

std::vector<std::shared_ptr<Output>> Output::outputs;

Output::Output(sf::Vector2i pos)
{
    setPosition(pos);
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
    sf::Vector2f containerPos = container.getPosition();

    pin.shape.setPosition(containerPos.x - containerBounds.width / 2, containerPos.y);
}

void Output::addOutput(std::shared_ptr<Output> output)
{
    outputs.push_back(std::move(output));
}

void Output::move(sf::Vector2f &delta)
{
    container.move(delta);
    indicator.move(delta);
    pin.shape.move(delta);
}

sf::Vector2f Output::getPosition()
{
    return container.getPosition();
}

bool Output::deleteHovered(const sf::Vector2f &pos)
{
    for (auto it = outputs.begin(); it != outputs.end(); ++it)
    {
        if ((*it)->contains(pos))
        {
            outputs.erase(it);
            return true;
        }
    }
    return false;
}

void Output::setState(bool state)
{
    pin.setState(state);
    indicator.setFillColor(
        getColor(
            state ? style::color::high
                  : style::color::low));
}