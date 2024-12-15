#include "components/Wire.hpp"

std::vector<std::unique_ptr<Wire>> Wire::wires;

Wire::Wire()
{
    std::cout << "created: wire" << std::endl;
    wire.setPrimitiveType(sf::TrianglesStrip);
    wire.clear();
    path.clear();

    //
    inputIndex = -1;
    outputIndex = -1;

    //
}

void Wire::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (path.size() < 2)
        return;

    target.draw(wire);
}

void Wire::addPoint(sf::Vector2i newPoint, int endSpecifier)
{
    if (visited.find(newPoint) != visited.end())
    {
        auto it = std::find(path.begin(), path.end(), newPoint);
        if (it != path.end())
        {
            auto toRemove = it;
            while (toRemove != path.end())
            {
                visited.erase(*toRemove);
                toRemove = path.erase(toRemove);
            }
        }
    }

    if (endSpecifier == 0)
        path.push_front(newPoint);
    else if (endSpecifier == 1)
        path.push_back(newPoint);
    visited.insert(newPoint);

    addWireToPath();
}

void Wire::updatePath(const sf::Vector2i &mouseGridPos, int endSpecifier)
{
    if (!path.empty())
    {
        sf::Vector2i lastPos{0, 0};
        if (endSpecifier == 0)
            lastPos = path.front();
        else if (endSpecifier == 1)
            lastPos = path.back();

        if (mouseGridPos != lastPos)
        {
            if (mouseGridPos.x != lastPos.x && mouseGridPos.y != lastPos.y)
            {
                addPoint({mouseGridPos.x, lastPos.y}, endSpecifier);
            }

            if (endSpecifier == 0 && mouseGridPos != path.front() || endSpecifier == 1 && mouseGridPos != path.back())
            {
                addPoint(mouseGridPos, endSpecifier);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
            {
                addPoint({mouseGridPos.x, lastPos.y}, endSpecifier);
            }
        }
    }
}

size_t Wire::VectorHash::operator()(const sf::Vector2i &v) const
{
    return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
}

void Wire::deleteWire()
{
    if (wires.empty())
        return;
    wires.clear();
    std::cout << "delete wires" << std::endl;
}

int Wire::getVertexCount()
{
    return wire.getVertexCount();
}

int Wire::getWireCount()
{
    return wires.size();
}

void Wire::addWire(std::unique_ptr<Wire> newWire)
{
    wires.emplace_back(std::move(newWire));
}

void Wire::addWireToPath()
{
    wire.clear();

    for (auto it = path.begin(); std::next(it) != path.end(); ++it)
    {
        sf::Vector2i start = *it;
        sf::Vector2i end = *std::next(it);

        sf::Vector2f startPos(start.x * sim::CELL_SIZE + sim::CELL_SIZE / 2, start.y * sim::CELL_SIZE + sim::CELL_SIZE / 2);
        sf::Vector2f endPos(end.x * sim::CELL_SIZE + sim::CELL_SIZE / 2, end.y * sim::CELL_SIZE + sim::CELL_SIZE / 2);

        float angle = std::atan2(endPos.y - startPos.y, endPos.x - startPos.x);
        float cosAngle = std::cos(angle);
        float sinAngle = std::sin(angle);

        sf::Vector2f offset(sim::WIRE_THICKNESS / 2 * sinAngle, -sim::WIRE_THICKNESS / 2 * cosAngle);

        sf::Vector2f p1 = startPos - offset;
        sf::Vector2f p2 = startPos + offset;
        sf::Vector2f p3 = endPos - offset;
        sf::Vector2f p4 = endPos + offset;

        wire.append(sf::Vertex(p1, getColor(style::color::low)));
        wire.append(sf::Vertex(p2, getColor(style::color::low)));
        wire.append(sf::Vertex(p3, getColor(style::color::low)));
        wire.append(sf::Vertex(p4, getColor(style::color::low)));
    }
}

void Wire::updateState()
{
    if (!(source && destination))
        return;
    state = (source->oPins[outputIndex]).getState();
    (destination->iPins[inputIndex]).setState(state);
    updateColor();
}

Wire::~Wire()
{
    std::cout << "deletd wire" << std::endl;
}

bool Wire::contains(sf::Vector2f pos)
{

    sf::FloatRect bounds = wire.getBounds();
    return bounds.contains(pos);
}

void Wire::updateColor()
{
    if (state)
        for (int i = 0; i < wire.getVertexCount(); i++)
        {
            wire[i].color = sf::Color(getColor(style::color::high));
        }

    else
        for (int i = 0; i < wire.getVertexCount(); i++)
        {
            wire[i].color = sf::Color(getColor(style::color::low));
        }
}

void Wire::updatePosition()
{
    if (source && outputIndex >= 0)
    {
        // path.push_front(sim::snapToGrid((source->oPins[outputIndex]).getPosition()));
        updatePath(sim::snapToGrid((source->oPins[outputIndex]).getPosition()), 0);
    }
    if (destination && inputIndex >= 0)
    {
        updatePath(sim::snapToGrid((destination->iPins[inputIndex]).getPosition()));
    }
}