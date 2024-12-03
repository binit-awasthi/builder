#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include "core/EventHandler.hpp"
#include "core/DrawHandler.hpp"
#include "utils/utils.hpp"

class App
{
private:
    sf::RenderWindow *window;
    void processEvents(EventHandler &);
    void update(EventHandler &);
    void render();
    void draw();
    void loadAssets();
    sf::ContextSettings settings;
    DrawHandler drawHandler;

public:
    App();
    ~App();
    void run();
};

#endif