#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include "utils/utils.hpp"

class Node : public sf::Drawable
{
    sf::RectangleShape rect;

public:
    Node(sf::Vector2i);
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
};

#endif