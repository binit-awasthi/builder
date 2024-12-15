#include "core/App.hpp"

App::App()
{
    settings.antialiasingLevel = 8;
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "builder", sf::Style::Fullscreen, settings);
    // window = std::make_unique<sf::RenderWindow>(sf::VideoMode(500, 500), "builder", sf::Style::None, settings);
    window->setFramerateLimit(60);
    loadAssets();

    /*
        sidebar = std::make_unique<Sidebar>(200, 600, std::vector<std::string>{"Start", "Settings", "Exit"});
        sidebar->setButtonCallback(0, []()
                                   { std::cout << "Start clicked!\n"; });
        sidebar->setButtonCallback(1, []()
                                   { std::cout << "Settings clicked!\n"; });
        sidebar->setButtonCallback(2, []()
                                   { std::cout << "Exit clicked!\n"; });
    */
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
    // sidebar->draw(*window);
}

void App::processEvents(EventHandler &eventHandler)
{

    sf::Event event;
    while (window->pollEvent(event))
    {
        // sidebar->handleEvent(event, *window);
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

    // sidebar->update(deltaTime);

    for (const auto &node : Node::nodes)
    {
        node->update();
    }

    for (const auto &wire : Wire::wires)
    {
        // wire->source->update();
        wire->updateState();
        // wire->destination->update();
    }
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
