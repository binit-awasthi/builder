#ifndef WIRE_HPP
#define WIRE_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <utils/utils.hpp>
#include <unordered_set>
#include <memory>
#include <cmath>
#include "components/Node.hpp"

class Wire : public sf::Drawable
{
    std::list<sf::Vector2i> path;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    struct VectorHash
    {
        size_t operator()(const sf::Vector2i &v) const;
    };
    std::unordered_set<sf::Vector2i, VectorHash> visited;
    sf::VertexArray wire;
    void addPathToWire();
    //

    bool state;
    //

public:
    Wire();
    ~Wire();
    void addPoint(sf::Vector2i newPoint);
    void updatePosition(sf::Vector2i &mouseGridPos);
    static void deleteWire();
    int getVertexCount();
    static std::vector<std::unique_ptr<Wire>> wires;
    static int getWireCount();
    static void addWire(std::unique_ptr<Wire>);
    void updateState();
    //
    std::shared_ptr<Node> source;
    std::shared_ptr<Node> destination;
    int inputIndex;
    int outputIndex;
    bool contains(sf::Vector2f);
    void updateColor();
    //
};

#endif
