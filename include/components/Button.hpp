#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "utils/utils.hpp"
#include <functional>
#include <string>
#include <SFML/Graphics.hpp>

struct Button : public sf::Drawable
{
public:
    Button(sf::Vector2i size = {sim::CELL_SIZE * 9, sim::CELL_SIZE * 5}, float cornerRdius = 6.f, sf::Color color = getColor(style::color::gate));
    sf::ConvexShape shape;
    sf::Text text;
    sf::Color normalColor;
    sf::Color hoverColor;
    float scale = 1.0f;
    float targetScale = 1.0f;
    std::function<void()> onClick;

    void update(float deltaTime);
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    bool contains(sf::Vector2f point) const;

    void setLabel(std::string = "button");
    void setPosition(sf::Vector2f pos = {0, 0});
};

#endif
