#include "core/DrawHandler.hpp"

std::vector<std::shared_ptr<sf::Drawable>> DrawHandler::itemsToDraw;

std::shared_ptr<sf::Drawable> DrawHandler::itemToDraw = nullptr;

void DrawHandler::draw(sf::RenderWindow &window)
{
    // for (auto item : itemsToDraw)
    // {
    //     if (item)
    //         window.draw(*item);
    // }

    if (itemToDraw)
    {
        window.draw(*itemToDraw);
    }

    for (const auto item : Wire::wires)
    {
        window.draw(*item);
    }
}
