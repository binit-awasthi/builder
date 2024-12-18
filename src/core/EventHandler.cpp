#include "core/EventHandler.hpp"

std::unique_ptr<Wire> EventHandler::wire = nullptr;

EventHandler::EventHandler(sf::RenderWindow &window) : window(window), isDragging(false), selectedNode(nullptr) {}

void EventHandler::handleEvents(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        sim::closeWindow(window);
        break;

    case sf::Event::KeyPressed:
        handleKeyPressEvents(event);
        break;

    case sf::Event::MouseButtonPressed:
        handleMousePressEvents(event);
        break;

    case sf::Event::MouseButtonReleased:
        handleMouseReleaseEvents(event);
        break;

    case sf::Event::MouseMoved:
        handleMouseMoveEvents(event);
        break;

    default:
        break;
    }
}

void EventHandler::handleKeyPressEvents(const sf::Event &event)
{
    if (event.key.control)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Q:
            sim::closeWindow(window);
            break;
        case sf::Keyboard::O:
            sim::fileOpener();
            break;
        case sf::Keyboard::C:
            Wire::deleteWires();
            break;
        default:
            break;
        }
    }
}

void EventHandler::handleMousePressEvents(const sf::Event &event)
{
    auto mousePos = sim::getMousePos(window);
    auto snappedPos = sim::snapToGrid(static_cast<sf::Vector2i>(mousePos));

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        handleLeftMousePress(mousePos, snappedPos);
    }
    else if (event.mouseButton.button == sf::Mouse::Right)
    {
        handleRightMousePress(mousePos);
    }
}

void EventHandler::handleLeftMousePress(const sf::Vector2f &mousePos, const sf::Vector2i &snappedPos)
{
    isDragging = true;
    wire = std::make_unique<Wire>();
    start = snappedPos;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
    {
        Node::addNode(std::make_unique<Node>(Node::Operation::NAND, snappedPos));
        selectedNode = Node::nodes.back().get();
        initialPos = mousePos;
        return;
    }

    //
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
    {
        selectedInputs.clear();
        Input::addInput(std::make_unique<Input>(snappedPos));
        selectedInputs.push_back(Input::inputs.back().get());
        initialPos = mousePos;
        return;
    }

    for (const auto &input : Input::inputs)
    {
        if ((input->pin).contains(mousePos))
        {
            wire->addPoint(start);
            wire->input = input.get();
            return;
        }
    }

    for (const auto &input : Input::inputs)
    {
        if (input->contains(mousePos))
        {
            selectedInputs.push_back(input.get());
            initialPos = mousePos;
        }

        if (input->indicator.getGlobalBounds().contains(mousePos))
        {
            input->indicatorOnClick();
            return;
        }
    }

    //

    if (checkHoverOutput(mousePos))
        return;

    Wire *hoveredWire = Wire::checkHovered(mousePos);
    if (hoveredWire)
    {
        this->wire->addPoint(start);
        this->wire->source = hoveredWire->source;
        this->wire->outputIndex = hoveredWire->outputIndex;
        this->wire->input = hoveredWire->input;
        return;
    }

    wire.reset();
}

void EventHandler::handleRightMousePress(const sf::Vector2f &mousePos)
{
    if (Wire::deleteHovered(mousePos))
        return;
    if (Node::deleteHovered(mousePos))
        return;
    if (Input::deleteHovered(mousePos))
        return;
}

void EventHandler::handleMouseReleaseEvents(const sf::Event &event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        isDragging = false;

        sf::Vector2f mousePos = sim::getMousePos(window);
        auto snappedPos = sim::snapToGrid(static_cast<sf::Vector2i>(mousePos));

        if (selectedNode)
        {
            selectedNode->setPosition(sim::snapToGrid(static_cast<sf::Vector2i>(selectedNode->getPosition())));
            selectedNode->hoverInactive();
            selectedNode = nullptr;
        }

        checkHoverInput(snappedPos);

        //
        for (const auto &input : selectedInputs)
            if (input)
            {
                input->setPosition(sim::snapToGrid(static_cast<sf::Vector2i>(input->getPosition())));
            }
        selectedInputs.clear();
        //
    }
}

void EventHandler::handleMouseMoveEvents(const sf::Event &event)
{
    moveSelected();
}

bool EventHandler::checkHoverOutput(const sf::Vector2f &pos)
{
    for (auto &node : Node::nodes)
    {
        for (int i = 0; i < node->oPins.size(); i++)
        {
            if (node->oPins[i].contains(pos))
            {
                wire->addPoint(start);
                wire->source = node;
                wire->outputIndex = i;
                return true;
            }
        }

        if (node->contains(pos))
        {
            selectedNode = node.get();
            initialPos = pos;
            return true;
        }
    }
    return false;
}

void EventHandler::moveSelected()
{
    auto mousePos = sim::getMousePos(window);
    auto delta = mousePos - initialPos;
    initialPos = mousePos;

    if (selectedNode)
    {
        selectedNode->move(delta);

        for (auto &wire : Wire::wires)
        {
            if ((wire->source.get() == selectedNode) || wire->destination.get() == selectedNode)
                wire->updatePosition();
        }
    }

    //
    for (const auto &input : selectedInputs)
        if (input)
        {
            input->move(delta);

            for (auto &wire : Wire::wires)
            {
                if (wire->input == input)
                    wire->updatePosition();
            }
        }
    //
}

void EventHandler::checkHoverInput(const sf::Vector2i &snappedPos)
{
    if (wire)
    {
        for (auto &node : Node::nodes)
        {
            for (int i = 0; i < node->iPins.size(); i++)
            {
                if (node->iPins[i].contains(sim::getMousePos(window)))
                {
                    wire->addPoint(snappedPos);
                    wire->destination = node;
                    wire->inputIndex = i;

                    if ((wire->outputIndex != -1 || wire->input) && wire->inputIndex != -1)
                    {
                        Wire *prevWire = node->iPins[wire->inputIndex].wire;
                        if (prevWire)
                        {
                            Wire::deleteWire(prevWire);
                        }

                        node->iPins[wire->inputIndex].wire = wire.get();

                        Wire::addWire(std::move(wire));
                        return;
                    }
                }
            }
        }
        wire.reset();
    }
}