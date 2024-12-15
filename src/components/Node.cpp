#include "components/Node.hpp"

std::vector<std::shared_ptr<Node>> Node::nodes;

Node::Node(Operation operation, sf::Vector2i pos, int nInput, int nOutput) : operation(operation)
{
    pinOffset = sim::CELL_SIZE;

    for (int i = 0; i < nInput; i++)
    {
        iPins.emplace_back();
    }
    for (int i = 0; i < nOutput; i++)
    {
        oPins.emplace_back();
    }

    setPosition(pos);
    shape.setLabel(getOperationName());
    setEvaluatorFunction();
}

void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape);
    for (const auto &pin : iPins)
    {
        target.draw(pin);
    }
    for (const auto &pin : oPins)
    {
        target.draw(pin);
    }
    target.draw(label);
}

void Node::updatePinPos()
{
    sf::Vector2f rectPos = shape.shape.getPosition();
    sf::FloatRect rectBounds = shape.shape.getLocalBounds();

    float leftX = rectPos.x - rectBounds.width / 2;
    float rightX = rectPos.x + rectBounds.width / 2;
    float nodeCenterY = rectPos.y;

    auto arrangePins = [](std::vector<Pin> &pins, float baseX, float centerY, float pinOffset)
    {
        int count = pins.size();

        if (count == 0)
            return;

        float startY = centerY;

        if (count % 2 == 1)
        {
            pins[count / 2].shape.setPosition(baseX, centerY);

            for (int i = 1; i <= count / 2; i++)
            {
                pins[count / 2 - i].shape.setPosition(baseX, centerY - i * pinOffset); // Above
                pins[count / 2 + i].shape.setPosition(baseX, centerY + i * pinOffset); // Below
            }
        }
        else
        {
            int topIndex = 0;
            int bottomIndex = count - 1;

            for (int i = 0; i < count / 2; i++)
            {
                pins[topIndex++].shape.setPosition(baseX, centerY - (count / 2 - i) * pinOffset);    // Top
                pins[bottomIndex--].shape.setPosition(baseX, centerY + (count / 2 - i) * pinOffset); // Bottom
            }
        }
    };

    arrangePins(iPins, leftX, nodeCenterY, pinOffset);

    arrangePins(oPins, rightX, nodeCenterY, pinOffset);
}

void Node::addNode(std::shared_ptr<Node> newNode)
{
    nodes.emplace_back(std::move(newNode));
}

void Node::deleteNodes()
{
    if (nodes.empty())
        return;
    nodes.clear();
    std::cout << "deleted all nodes" << std::endl;
}

//

void Node::update()
{
    evaluate();
}

void Node::setEvaluatorFunction()
{
    switch (operation)
    {
    case Operation::AND:
        evaluator = [](const std::vector<bool> &inputs)
        {
            for (bool input : inputs)
            {
                if (!input)
                    return false;
            }
            return true;
        };
        break;
    case Operation::OR:
        evaluator = [](const std::vector<bool> &inputs)
        {
            for (bool input : inputs)
            {
                if (input)
                    return true;
            }
            return false;
        };
        break;
    case Operation::NOT:
        evaluator = [](const std::vector<bool> &inputs)
        {
            if (inputs.size() != 1)
            {
                throw std::invalid_argument("NOT gate requires exactly one input.");
            }
            return !inputs[0];
        };
        break;
    case Operation::XOR:
        evaluator = [](const std::vector<bool> &inputs)
        {
            bool result = false;
            for (bool input : inputs)
            {
                result ^= input;
            }
            return result;
        };
        break;
    case Operation::NAND:
        evaluator = [](const std::vector<bool> &inputs)
        {
            for (bool input : inputs)
            {
                if (!input)
                    return true;
            }
            return false;
        };
        break;
    case Operation::NOR:
        evaluator = [](const std::vector<bool> &inputs)
        {
            for (bool input : inputs)
            {
                if (input)
                    return false;
            }
            return true;
        };
        break;
    case Operation::BUFFER:
        evaluator = [](const std::vector<bool> &inputs)
        {
            if (inputs.size() != 1)
            {
                throw std::invalid_argument("BUFFER gate requires exactly one input.");
            }
            return inputs[0];
        };
        break;
    default:
        throw std::invalid_argument("Invalid operation.");
    }
}

void Node::evaluate()
{
    std::vector<bool> inputs;
    for (auto &iPin : iPins)
    {
        inputs.push_back(iPin.getState());
    }

    oPins[0].setState(evaluator(inputs));
}

std::string Node::getOperationName() const
{
    switch (operation)
    {
    case Operation::AND:
        return "AND";
    case Operation::OR:
        return "OR";
    case Operation::NOT:
        return "NOT";
    case Operation::XOR:
        return "XOR";
    case Operation::NAND:
        return "NAND";
    case Operation::NOR:
        return "NOR";
    case Operation::BUFFER:
        return "BUFFER";
    default:
        return "UNKNOWN";
    }
}

//

bool Node::contains(sf::Vector2f pos)
{
    return shape.contains(pos);
}

void Node::setPosition(sf::Vector2i pos)
{
    shape.setPosition({pos.x * sim::CELL_SIZE + (float)sim::CELL_SIZE / 2, pos.y * sim::CELL_SIZE + (float)sim::CELL_SIZE / 2});
    updatePinPos();
}

void Node::move(const sf::Vector2f &delta)
{

    shape.shape.move(delta);
    shape.text.move(delta);

    for (auto &pin : iPins)
        pin.shape.move(delta);

    for (auto &pin : oPins)
        pin.shape.move(delta);
}

sf::Vector2f Node::getPosition()
{
    return (shape.shape.getPosition());
}
