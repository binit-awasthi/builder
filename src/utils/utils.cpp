#include "utils/utils.hpp"

sf::Font sim::font;
sf::Image sim::icon;

const int sim::CELL_SIZE = 10;
const float sim::WIRE_THICKNESS = 5.0f;

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

sim::Direction sim::getDirection(const sf::Vector2f &start, const sf::Vector2f &end)
{
    if (start.x != end.x && start.y == end.y)
        return Horizontal;
    if (start.y != end.y && start.x == end.x)
        return Vertical;

    return None;
}

sf::Vector2i sim::snapToGrid(const sf::Vector2i &position)
{
    return {position.x / sim::CELL_SIZE, position.y / sim::CELL_SIZE};
}

sf::Color getColor(style::color color)
{
    switch (color)
    {
    case style::color::gate:
        return sf::Color(247, 44, 91);
    case style::color::low:
        return sf::Color(98, 94, 94);
    case style::color::high:
        return sf::Color(230, 233, 234);

    case style::color::selected:
        return sf::Color(12, 140, 233);

    case style::color::window:
        return sf::Color(30, 30, 30, 1);

    default:
        return sf::Color::White;
    }
}

void sim::drawGrid(sf::RenderWindow &window)
{
    sf::Vector2u windowSize = window.getSize();
    int gridWidth = windowSize.x / CELL_SIZE;
    int gridHeight = windowSize.y / CELL_SIZE;

    for (int x = 0; x < gridWidth; ++x)
    {
        for (int y = 0; y < gridHeight; ++y)
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            cell.setFillColor(sf::Color::White);
            window.draw(cell);
        }
    }
}

sf::ConvexShape sim::createRoundedRect(float width, float height, float radius, sf::Color color)
{
    const int cornerPoints = 10;
    sf::ConvexShape shape(4 * (cornerPoints + 1));

    shape.setFillColor(color);

    float angleStep = 90.0f / cornerPoints;
    int index = 0;

    // Top-left corner
    for (int i = 0; i <= cornerPoints; ++i)
    {
        float angle = (180 + i * angleStep) * (M_PI / 180.0f); // Convert to radians
        shape.setPoint(index++, {radius + radius * std::cos(angle), radius + radius * std::sin(angle)});
    }

    // Top-right corner
    for (int i = 0; i <= cornerPoints; ++i)
    {
        float angle = (270 + i * angleStep) * (M_PI / 180.0f);
        shape.setPoint(index++, {width - radius + radius * std::cos(angle), radius + radius * std::sin(angle)});
    }

    // Bottom-right corner
    for (int i = 0; i <= cornerPoints; ++i)
    {
        float angle = (0 + i * angleStep) * (M_PI / 180.0f);
        shape.setPoint(index++, {width - radius + radius * std::cos(angle), height - radius + radius * std::sin(angle)});
    }

    // Bottom-left corner
    for (int i = 0; i <= cornerPoints; ++i)
    {
        float angle = (90 + i * angleStep) * (M_PI / 180.0f);
        shape.setPoint(index++, {radius + radius * std::cos(angle), height - radius + radius * std::sin(angle)});
    }

    return shape;
}