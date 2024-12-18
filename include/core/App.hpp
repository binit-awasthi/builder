#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include "core/EventHandler.hpp"
#include "core/DrawHandler.hpp"
#include "utils/utils.hpp"
#include <memory>
#include "components/SideBar.hpp"

class App
{
private:
    std::unique_ptr<sf::RenderWindow> window;

    void processEvents(EventHandler &);
    void update(EventHandler &);
    void render();
    void draw();
    void loadAssets();
    sf::ContextSettings settings;
    DrawHandler drawHandler;
    //
    // std::unique_ptr<Sidebar> sidebar;
    sf::Clock clock;
    float deltaTime;
    //
public:
    App();
    ~App();
    void run();
};

#endif