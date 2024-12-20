#pragma once

#include <SFML/Graphics.hpp>
#include "components/Indicator.hpp"
#include "utils/utils.hpp"
#include <memory>

class Output : public Indicator
{
public:
    static std::vector<std::shared_ptr<Output>> outputs;

    Pin pin;
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    void setPosition(const sf::Vector2i &pos = {100, 100});

    void move(sf::Vector2f &);
    sf::Vector2f getPosition();
    void setState(bool state);

    static void addOutput(std::shared_ptr<Output>);
    static bool deleteHovered(const sf::Vector2f &pos);

    Output(sf::Vector2i pos = {100, 100});
};