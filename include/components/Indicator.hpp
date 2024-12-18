#pragma once

#include <SFML/Graphics.hpp>
#include "components/Pin.hpp"
#include "utils/utils.hpp"

class Indicator : public sf::Drawable
{
protected:
    sf::ConvexShape container;
    float indicatorRadius;
    float containerHeight;

public:
    sf::CircleShape indicator;
    Indicator();
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    virtual void setPosition(const sf::Vector2i &pos = {0, 0});
    virtual bool contains(sf::Vector2f pos);
};
