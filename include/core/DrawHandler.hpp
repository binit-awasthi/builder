#ifndef DRAWHANDLER_HPP
#define DRAWHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "components/Wire.hpp"
#include "core/EventHandler.hpp"

class DrawHandler
{
private:
    int count;

public:
    void draw(sf::RenderWindow &);
    static std::vector<std::shared_ptr<sf::Drawable>> itemsToDraw;
    // static std::shared_ptr<sf::Drawable> itemToDraw ;
};

#endif