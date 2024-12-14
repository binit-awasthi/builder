#include "components/sideBar.hpp"

Sidebar::Sidebar(float width, float height, const std::vector<std::string> &buttonLabels)
{
    for (size_t i = 0; i < buttonLabels.size(); ++i)
    {
        Button button;
        button.shape = sim::createRoundedRect(width, buttonHeight, cornerRadius, normalColor);
        button.shape.setPosition(0, i * (buttonHeight + padding));
        button.text.setFont(sim::font);
        button.text.setString(buttonLabels[i]);
        button.text.setCharacterSize(20);
        button.text.setFillColor(sf::Color::White);
        button.text.setPosition(button.shape.getPosition().x + 10, button.shape.getPosition().y + 10);
        button.normalColor = normalColor;
        button.hoverColor = hoverColor;
        button.shape.setOutlineThickness(1.f);
        button.shape.setOutlineColor(sf::Color(30, 144, 255, 153));
        buttons.push_back(button);
        //
    }
}

void Sidebar::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    for (auto &button : buttons)
    {
        if (button.contains(mousePos))
        {
            button.targetScale = 1.1f;
            button.hoverColor = sf::Color(0, 123, 255, 100);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (button.onClick)
                    button.onClick();
            }
        }
        else
        {
            button.targetScale = 1.0f;
            button.hoverColor = sf::Color(0, 123, 255, 0.8);
        }
    }
}

void Sidebar::update(float deltaTime)
{
    for (auto &button : buttons)
    {
        button.update(deltaTime);
    }
}

void Sidebar::draw(sf::RenderWindow &window) const
{
    for (const auto &button : buttons)
    {
        window.draw(button);
    }
}

void Sidebar::setButtonCallback(size_t index, std::function<void()> callback)
{
    if (index < buttons.size())
    {
        buttons[index].onClick = callback;
    }
}

