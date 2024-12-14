#include "components/button.hpp"

Button::Button(sf::Vector2i size, float cornerRdius, sf::Color color)
{
    shape = sim::createRoundedRect(size.x, size.y, cornerRdius, color);
    sf::FloatRect shapeBounds = shape.getLocalBounds();
    shape.setOrigin(shapeBounds.width / 2, shapeBounds.height / 2);
    setPosition();
    setLabel();
}

void Button::update(float deltaTime)
{
    scale = sim::lerp(scale, targetScale, deltaTime * 5.0f);

    shape.setScale(scale, scale);
    text.setScale(scale, scale);

    sf::Color currentColor = shape.getFillColor();
    sf::Color newColor(
        sim::lerp(currentColor.r, hoverColor.r, deltaTime * 5.0f),
        sim::lerp(currentColor.g, hoverColor.g, deltaTime * 5.0f),
        sim::lerp(currentColor.b, hoverColor.b, deltaTime * 5.0f),
        sim::lerp(currentColor.a, hoverColor.a, deltaTime * 5.0f));
    shape.setFillColor(newColor);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape);
    target.draw(text);
}

bool Button::contains(sf::Vector2f point) const
{
    return shape.getGlobalBounds().contains(point);
}

void Button::setLabel(std::string label)
{
    text.setFont(sim::font);
    text.setString(label);
    text.setCharacterSize(16);
    // text.setFillColor(sf::Color::White);
    text.setFillColor(getColor(style::color::low));
    text.setStyle(sf::Text::Bold);
}

void Button::setPosition(sf::Vector2f pos)
{
    shape.setPosition(pos);
    sf::FloatRect shapeBounds = shape.getLocalBounds();
    text.setPosition(pos.x - 16, pos.y - 8);
}