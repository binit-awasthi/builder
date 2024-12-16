#ifndef PIN_HPP
#define PIN_HPP

#include <SFML/Graphics.hpp>
#include "utils/utils.hpp"

class Wire;

class Pin : public sf::Drawable
{

    bool state;

public:
    sf::CircleShape shape;
    Pin(bool state = false);
    void setState(bool state);
    bool getState();
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    bool contains(sf::Vector2f point) const;
    sf::Vector2i getPosition();
    void hoverActive();
    void hoverInactive();
    Wire *wire;
};

#endif