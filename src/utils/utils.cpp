#include "utils/utils.hpp"

void sim::fileOpener()
{
    const char *filePath = tinyfd_openFileDialog(
        "Open a File",
        "",
        0, nullptr, nullptr, 0);

    if (filePath)
    {
        std::cout << "File selected: " << filePath << std::endl;
    }
    else
    {
        std::cout << "No file selected" << std::endl;
    }
}

void sim::closeWindow(sf::RenderWindow &window)
{
    window.close();
    std::cout << "window closed successfully" << std::endl;
}
sf::Vector2f sim::getMousePos(sf::RenderWindow &window)
{
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
}

sf::Font sim::font;
sf::Image sim::icon;

void sim::loadAssets()
{
    if (!font.loadFromFile("../assets/fonts/Poppins-Regular.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
    }
    icon.loadFromFile("../assets/images/icon.png");
}

float sim::distance(const sf::Vector2f &point1, const sf::Vector2f &point2)
{
    float dx = point1.x - point2.x;
    float dy = point1.y - point2.y;
    return std::sqrt(dx * dx + dy * dy);
}

float sim::getAngle(sf::Vector2f start, sf::Vector2f end)
{
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    return std::atan2(dy, dx) * 180 / M_PI;
}