#ifndef DRAWHANDLER_HPP
#define DRAWHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "components/Wire.hpp"
#include "components/ElementalWire.hpp"

class DrawHandler
{
private:
    int count;

public:
    DrawHandler();
    ~DrawHandler();
    void draw(sf::RenderWindow &);
    static std::vector<sf::Drawable *> itemsToDraw;
};

#endif