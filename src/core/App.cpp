#include "core/App.hpp"

App::App()
{
    settings.antialiasingLevel = 8;
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "builder", sf::Style::Fullscreen, settings);
    // window = std::make_unique<sf::RenderWindow>(sf::VideoMode(500, 500), "builder", sf::Style::None, settings);
    window->setFramerateLimit(60);
    loadAssets();
}

void App::run()
{
    EventHandler eventHandler(*window);

    while (window->isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        processEvents(eventHandler);
        update(eventHandler);
        render();
    }
}

void App::render()
{
    window->clear(getColor(style::color::window));
    draw();
    window->display();
}

void App::draw()
{
    drawHandler.draw(*window);
}

void App::processEvents(EventHandler &eventHandler)
{

    sf::Event event;
    while (window->pollEvent(event))
    {
        eventHandler.handleEvents(event);
    }
}

void App::update(EventHandler &eventHandler)
{
    if (eventHandler.isDragging)
    {
        if (eventHandler.wire)
        {
            sf::Vector2i mouseGridPos = sim::snapToGrid(sf::Mouse::getPosition(*window));
            eventHandler.wire->updatePath(mouseGridPos);
        }
    }

    Wire::updateAllWires();

    if (eventHandler.selectedNode)
        eventHandler.selectedNode->hoverActive();
}

void App::loadAssets()
{
    sim::loadAssets();
    window->setIcon(sim::icon.getSize().x, sim::icon.getSize().y, sim::icon.getPixelsPtr());
}

App::~App()
{
    std::cout << "exited app" << std::endl;
}
