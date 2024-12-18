#ifndef DRAWHANDLER_HPP
#define DRAWHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "components/Wire.hpp"
#include "components/Button.hpp"
#include "components/Input.hpp"
#include "components/Output.hpp"
#include "core/EventHandler.hpp"

class DrawHandler
{
public:
    void draw(sf::RenderWindow &);
    static std::vector<std::shared_ptr<sf::Drawable>> itemsToDraw;
};

#endif