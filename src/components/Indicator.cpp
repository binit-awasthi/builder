#include "components/Indicator.hpp"

Indicator::Indicator()
{
    // indicatorRadius = 9.f;
    // containerHeight = 34.f;
    containerHeight = sim::CELL_SIZE * 3;
    indicatorRadius = sim::CELL_SIZE;

    indicator.setFillColor(getColor(style::color::low));

    container = sim::createRoundedRect(containerHeight, containerHeight, 6.f, getColor(style::color::container));
    sf::FloatRect containerBounds = container.getLocalBounds();
    container.setOrigin(containerBounds.width / 2, containerBounds.height / 2);
    setPosition();
}

void Indicator::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(container);
    target.draw(indicator);
}

void Indicator::setPosition(const sf::Vector2i &pos)
{
    container.setPosition({pos.x * sim::CELL_SIZE + (float)sim::CELL_SIZE / 2, pos.y * sim::CELL_SIZE + (float)sim::CELL_SIZE / 2});
    indicator.setRadius(indicatorRadius);
    indicator.setOrigin(indicatorRadius, indicatorRadius);
    indicator.setPosition({pos.x * sim::CELL_SIZE + (float)sim::CELL_SIZE / 2, pos.y * sim::CELL_SIZE + (float)sim::CELL_SIZE / 2});
}

bool Indicator::contains(sf::Vector2f pos)
{
    return (container.getGlobalBounds().contains(pos));
}
