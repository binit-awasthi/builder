#include "core/EventHandler.hpp"

std::shared_ptr<Wire> EventHandler::wire = nullptr;

EventHandler::EventHandler(sf::RenderWindow &window)
    : window(window), isDragging(false), selectedNode(nullptr) {}

void EventHandler::handleEvents(const sf::Event &event)
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
    wire = std::make_shared<Wire>();
    start = snappedPos;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
    {
        Node::addNode(std::make_shared<Node>(Node::Operation::NAND, snappedPos));
        selectedNode = Node::nodes.back().get();
        initialPos = mousePos;
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
    {
        Output::addOutput(std::make_shared<Output>(snappedPos));
        selectedOutputs.push_back(Output::outputs.back());
        initialPos = mousePos;
        return;
    }

    for (const auto &output : Output::outputs)
    {
        if (output->contains(mousePos))
        {
            selectedOutputs.push_back(output);
            initialPos = mousePos;
            return;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
    {
        Input::addInput(std::make_shared<Input>(snappedPos));
        selectedInputs.push_back(Input::inputs.back());
        initialPos = mousePos;
        return;
    }

    for (const auto &input : Input::inputs)
    {
        if ((input->pin).contains(mousePos))
        {
            wire->addPoint(start);
            wire->input = input;
            return;
        }
    }

    if (checkHoverOutput(mousePos))
        return;

    auto hoveredWire = Wire::checkHovered(mousePos);
    if (hoveredWire)
    {
        wire->addPoint(start);
        wire->source = hoveredWire->source;
        wire->outputIndex = hoveredWire->outputIndex;
        wire->input = hoveredWire->input;
        return;
    }

    wire.reset();
}

void EventHandler::handleRightMousePress(const sf::Vector2f &mousePos)
{
    if (Wire::deleteHovered(mousePos) || Node::deleteHovered(mousePos) ||
        Input::deleteHovered(mousePos) || Output::deleteHovered(mousePos))
        return;
}

void EventHandler::handleMouseReleaseEvents(const sf::Event &event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        isDragging = false;

        auto mousePos = sim::getMousePos(window);
        auto snappedPos = sim::snapToGrid(static_cast<sf::Vector2i>(mousePos));

        if (selectedNode)
        {
            selectedNode->setPosition(snappedPos);
            selectedNode->hoverInactive();
            selectedNode = nullptr;
        }

        checkHoverInput(snappedPos);
        resetSelections();
    }
}

void EventHandler::handleMouseMoveEvents(const sf::Event &event)
{
    moveSelected();
}

void EventHandler::checkHoverInput(const sf::Vector2i &snappedPos)
{
    if (wire)
    {
        for (const auto &node : Node::nodes)
        {
            for (size_t i = 0; i < node->iPins.size(); ++i)
            {
                if (node->iPins[i].contains(sim::getMousePos(window)))
                {
                    wire->addPoint(snappedPos);
                    wire->destination = node;
                    wire->inputIndex = i;

                    auto prevWire = node->iPins[i].wire;
                    if (prevWire)
                    {
                        Wire::removeWire(prevWire);
                    }

                    node->iPins[i].wire = wire;
                    Wire::addWire(wire);
                    return;
                }
            }
        }

        for (const auto &output : Output::outputs)
        {
            if (output->pin.contains(sim::getMousePos(window)))
            {
                wire->addPoint(snappedPos);
                wire->output = output;

                auto prevWire = output->pin.wire;
                if (prevWire)
                {
                    Wire::removeWire(prevWire);
                }

                output->pin.wire = wire;
                Wire::addWire(wire);
                return;
            }
        }

        wire.reset();
    }
}

bool EventHandler::checkHoverOutput(const sf::Vector2f &pos)
{
    for (const auto &node : Node::nodes)
    {
        for (size_t i = 0; i < node->oPins.size(); ++i)
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

    for (const auto &input : Input::inputs)
    {
        if (input->track.getGlobalBounds().contains(pos))
        {
            input->indicatorOnClick();
        }

        if (input->contains(pos))
        {
            selectedInputs.push_back(input);
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
            if (wire->source.get() == selectedNode || wire->destination.get() == selectedNode)
                wire->updatePosition();
        }
    }

    for (const auto &input : selectedInputs)
    {
        input->move(delta);

        for (auto &wire : Wire ::wires)
        {
            if (wire->input == input)
                wire->updatePosition();
        }
    }

    for (const auto &output : selectedOutputs)
    {
        output->move(delta);

        for (auto &wire : Wire::wires)
        {
            if (wire->output == output)
                wire->updatePosition();
        }
    }
}

void EventHandler::resetSelections()
{
    for (const auto &input : selectedInputs)
    {
        if (input)
        {
            input->setPosition(sim::snapToGrid(static_cast<sf::Vector2i>(input->getPosition())));
        }
    }
    selectedInputs.clear();

    for (const auto &output : selectedOutputs)
    {
        if (output)
        {
            output->setPosition(sim::snapToGrid(static_cast<sf::Vector2i>(output->getPosition())));
        }
    }
    selectedOutputs.clear();
}