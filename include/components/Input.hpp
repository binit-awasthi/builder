#pragma once

#include <SFML/Graphics.hpp>
#include "components/Pin.hpp"
#include "components/Indicator.hpp"
#include "utils/utils.hpp"
#include <memory>

class Wire;

class Input : public Indicator
{

    float trackWidth = 6.f;
    float sliderRadius = 5.f;
    sf::FloatRect trackBounds;

public:
    Input(sf::Vector2i pos = {100, 100});

    static std::vector<std::shared_ptr<Input>> inputs;
    static bool deleteHovered(const sf::Vector2f &pos);

    static void addInput(std::shared_ptr<Input>);

    Pin pin;
    sf::ConvexShape track;
    sf::CircleShape slider;
    void setPosition(const sf::Vector2i &pos = {100, 100});
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    void move(sf::Vector2f &);
    sf::Vector2f getPosition();
    void indicatorOnClick();
};
