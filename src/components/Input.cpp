#include "components/Input.hpp"

std::vector<std::unique_ptr<Input>> Input::inputs;

Input::Input(sf::Vector2i pos)
{
    slider.setRadius(sliderRadius);
    slider.setFillColor(getColor(style::color::slider));
    slider.setOrigin(sliderRadius, sliderRadius);

    track = sim::createRoundedRect(trackWidth, containerHeight * 0.5, trackWidth / 2, getColor(style::color::track));
    trackBounds = track.getLocalBounds();
    track.setOrigin(trackBounds.width / 2, trackBounds.height / 2);

    setPosition(pos);
}

void Input::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Indicator::draw(target, states);
    target.draw(track);
    target.draw(slider);
    target.draw(pin);
}

void Input::setPosition(const sf::Vector2i &pos)
{
    Indicator::setPosition(pos);

    sf::FloatRect containerBounds = container.getLocalBounds();
    sf::Vector2f containerPos = container.getPosition();

    track.setPosition(containerPos.x - containerBounds.width / 2 + trackBounds.width / 2, containerPos.y);

    sf::Vector2f trackPos = track.getPosition();
    slider.setPosition(trackPos.x, trackPos.y - trackBounds.height / 2);

    pin.shape.setPosition(containerPos.x + containerBounds.width / 2, containerPos.y);
}

void Input::addInput(std::unique_ptr<Input> input)
{
    inputs.push_back(std::move(input));
}

void Input::move(sf::Vector2f &delta)
{
    container.move(delta);
    indicator.move(delta);
    slider.move(delta);
    track.move(delta);
    pin.shape.move(delta);
}

sf::Vector2f Input::getPosition()
{
    return container.getPosition();
}

void Input::indicatorOnClick()
{
    pin.setState(!pin.getState());
    indicator.setFillColor(
        getColor(
            (pin.getState()) ? style::color::high : style::color::low));
}

bool Input::deleteHovered(const sf::Vector2f &pos)
{
    for (auto it = inputs.begin(); it != inputs.end(); ++it)
    {
        if ((*it)->contains(pos))
        {
            inputs.erase(it);
            return true;
        }
    }
    return false;
}