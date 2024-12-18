#ifndef SIDEBAR_HPP
#define SIDEBAR_HPP

#include <vector>
#include <functional>
#include <cmath>
#include <components/Button.hpp>
#include <SFML/Graphics.hpp>
#include <utils/utils.hpp>

class Sidebar
{
private:
    std::vector<Button> buttons;
    float buttonHeight = 50.0f;
    float padding = 5.0f;
    float cornerRadius = 25.0f;
    sf::Color normalColor = sf::Color(100, 100, 100);
    sf::Color hoverColor = sf::Color(150, 150, 250);

public:
    Sidebar(float width, float height, const std::vector<std::string> &buttonLabels);

    void handleEvent(const sf::Event &event, sf::RenderWindow &window);
    void update(float deltaTime);
    void draw(sf::RenderWindow &window) const;
    void setButtonCallback(size_t index, std::function<void()> callback);
    sf::ConvexShape createRoundedRect(float width, float height, float radius, sf::Color color);
};

#endif