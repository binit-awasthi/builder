#ifndef PIN_HPP
#define PIN_HPP

#include <SFML/Graphics.hpp>
#include "utils/utils.hpp"
#include <memory>

class Wire;

class Pin : public sf::Drawable
{

    bool state;

public:
    sf::CircleShape shape;
    std::shared_ptr<Wire> wire;

    void setState(bool state);
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    bool getState();
    bool contains(sf::Vector2f point) const;
    void hoverActive();
    void hoverInactive();
    sf::Vector2i getPosition();

    Pin(bool state = false);
};

#endif