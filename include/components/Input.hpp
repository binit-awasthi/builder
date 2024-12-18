#pragma once

#include <SFML/Graphics.hpp>
#include "components/Pin.hpp"
#include "components/Indicator.hpp"
#include "utils/utils.hpp"
#include <memory>

class Input : public Indicator
{
    sf::ConvexShape track;

    float trackWidth = 6.f;
    float sliderRadius = 5.f;
    sf::FloatRect trackBounds;

public:
    static std::vector<std::unique_ptr<Input>> inputs;

    Pin pin;
    sf::CircleShape slider;
    Input(sf::Vector2i pos = {100, 100});
    void setPosition(const sf::Vector2i &pos = {100, 100});
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    void move(sf::Vector2f &);
    sf::Vector2f getPosition();
    void indicatorOnClick();

    static void addInput(std::unique_ptr<Input>);
    static bool deleteHovered(const sf::Vector2f &pos);
};
