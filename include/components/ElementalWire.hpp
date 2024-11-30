#ifndef WIRE_HPP
#define WIRE_HPP

#include <SFML/Graphics.hpp>
#include <utils/utils.hpp>

class ElementalWire : public sf::Drawable
{
    sf::Vector2f start;
    sf::Vector2f end;
    sf::RectangleShape rect;
    float thickness;

public:
    ElementalWire(sf::Vector2f, sf::Vector2f);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void setWidth(float width);
    void setEnd(sf::Vector2f);
};

#endif