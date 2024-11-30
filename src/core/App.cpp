#include "core/App.hpp"

App::App()
{
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML Project", sf::Style::None, settings);
    window->setFramerateLimit(60);
    loadAssets();
}

void App::run()
{
    EventHandler eventHandler(*window);

    while (window->isOpen())
    {
        processEvents(eventHandler);
        update();
        render();
    }
}

void App::render()
{
    window->clear(sf::Color(30, 30, 30, 1));
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

void App::update()
{
}

void App::loadAssets()
{
    sim::loadAssets();
    window->setIcon(sim::icon.getSize().x, sim::icon.getSize().y, sim::icon.getPixelsPtr());
}

App::~App()
{
    delete window;
}