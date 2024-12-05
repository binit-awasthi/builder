#include "components/Node.hpp"

Node::Node(sf::Vector2i pos)
{
    rect.setSize({(float)sim::CELL_SIZE * 9, (float)sim::CELL_SIZE * 5});
    sf::FloatRect bounds = rect.getLocalBounds();
    rect.setOrigin(bounds.width / 2, bounds.height / 2);
    rect.setFillColor(getColor(style::color::gate));

    rect.setPosition(pos.x * sim::CELL_SIZE + sim::CELL_SIZE / 2, pos.y * sim::CELL_SIZE + sim::CELL_SIZE / 2);
}

void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect);
}