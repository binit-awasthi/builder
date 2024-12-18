#pragma once

#include <SFML/Graphics.hpp>
#include "components/Indicator.hpp"
#include <memory>

class Output : public Indicator
{
public:
    static std::vector<std::unique_ptr<Output>> outputs;

    Pin pin;
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    void setPosition(const sf::Vector2i &pos = {100, 100});
    Output();
};