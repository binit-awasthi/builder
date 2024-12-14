#include "core/DrawHandler.hpp"

std::vector<std::shared_ptr<sf::Drawable>> DrawHandler::itemsToDraw;

void DrawHandler::draw(sf::RenderWindow &window)
{

    if (EventHandler::wire)
    {
        window.draw(*EventHandler::wire);
    }

    for (const auto &item : Wire::wires)
    {
        window.draw(*item);
    }
    for (const auto item : itemsToDraw)
    {
        if (item)
            window.draw(*item);
    }
    for (const auto &node : Node::nodes)
    {
        if (node)
            window.draw(*node);
    }
}
