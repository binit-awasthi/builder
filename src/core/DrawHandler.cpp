#include "core/DrawHandler.hpp"

std::vector<sf::Drawable *> DrawHandler::itemsToDraw;

DrawHandler::DrawHandler()
{
    count = 0;
}

void DrawHandler::draw(sf::RenderWindow &window)
{
    for (auto item : itemsToDraw)
    {
        window.draw(*item);
    }
    
}

DrawHandler::~DrawHandler()
{
    for (auto item : itemsToDraw)
    {
        delete item;
    }
}
