#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <functional>
#include <cmath>
#include "utils/utils.hpp"
#include "components/Pin.hpp"
#include "components/button.hpp"

class Node : public sf::Drawable
{
public:
    enum class Operation
    {
        AND,
        OR,
        NOT,
        XOR,
        NAND,
        NOR,
        BUFFER
    };

private:
    Button shape;
    float pinOffset;
    sf::Text label;
    Operation operation;
    std::function<bool(const std::vector<bool> &)> evaluator;

public:
    std::vector<Pin> iPins;
    std::vector<Pin> oPins;

    static std::vector<std::shared_ptr<Node>> nodes;

    static void addNode(std::shared_ptr<Node>);
    static void deleteNodes();
    static bool deleteHovered(const sf::Vector2f &pos);

    void setPosition(sf::Vector2i);
    void move(const sf::Vector2f &delta);
    void hoverInactive();
    void hoverActive();
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    void updatePinPos();
    void evaluate();
    void update();
    void setEvaluatorFunction();
    bool contains(sf::Vector2f);
    sf::Vector2f getPosition();
    std::string getOperationName() const;

    Node(Operation, sf::Vector2i, int nInput = 2, int nOutput = 1);
};

#endif