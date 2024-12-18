#include "core/DrawHandler.hpp"

std::vector<std::shared_ptr<sf::Drawable>> DrawHandler::itemsToDraw;

void DrawHandler::draw(sf::RenderWindow &window)
{

    for (const auto &item : Wire::wires)
    {
        window.draw(*item);
    }

    for (const auto &item : Input::inputs)
    {
        window.draw(*item);
    }

    for (const auto &item : Output::outputs)
    {
        window.draw(*item);
    }

    if (EventHandler::wire)
    {
        window.draw(*EventHandler::wire);
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
