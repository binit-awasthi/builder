#ifndef WIRE_HPP
#define WIRE_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <utils/utils.hpp>
#include <unordered_set>
#include <memory>
#include <cmath>
#include "components/Node.hpp"
#include "components/Input.hpp"

class Wire : public sf::Drawable
{
    std::list<sf::Vector2i> path;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    struct VectorHash
    {
        size_t operator()(const sf::Vector2i &v) const;
    };
    std::unordered_set<sf::Vector2i, VectorHash> visitedPoints;
    sf::VertexArray wire;
    void addWireToPath();
    sf::Color color;

public:
    bool state;
    int inputIndex;
    int outputIndex;
    Input *input;

    std::shared_ptr<Node> source;
    std::shared_ptr<Node> destination;

    static std::vector<std::unique_ptr<Wire>> wires;
    static void deleteWire(Wire *);
    static void deleteWires();
    static int getWireCount();
    static void addWire(std::unique_ptr<Wire>);
    static bool deleteHovered(const sf::Vector2f &);
    static Wire *checkHovered(const sf::Vector2f &);

    void addPoint(sf::Vector2i newPoint, int endSpecifier = 1);
    void updatePath(const sf::Vector2i &mouseGridPos, int endSpecifier = 1);
    void updateColor();
    void updatePosition();
    static void updateAllWires();
    bool contains(sf::Vector2f);
    int getVertexCount();

    Wire();
    ~Wire();
};

#endif
