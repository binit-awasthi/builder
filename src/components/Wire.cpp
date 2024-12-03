#include "components/Wire.hpp"

Wire::Wire()
{
    std::cout << "created: wire" << std::endl;
    path.clear();
}

void Wire::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (path.size() < 2)
        return;

    sf::VertexArray wire(sf::TrianglesStrip);

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

        wire.append(sf::Vertex(p1, sf::Color::White));
        wire.append(sf::Vertex(p2, sf::Color::White));
        wire.append(sf::Vertex(p3, sf::Color::White));
        wire.append(sf::Vertex(p4, sf::Color::White));
    }

    target.draw(wire);
}

void Wire::addPoint(sf::Vector2i newPoint)
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

    path.push_back(newPoint);
    visited.insert(newPoint);
}

void Wire::updatePosition(sf::Vector2i &mouseGridPos)
{

    if (!path.empty())
    {
        sf::Vector2i lastPos = path.back();

        if (mouseGridPos != lastPos)
        {
            if (mouseGridPos.x != lastPos.x && mouseGridPos.y != lastPos.y)
            {
                addPoint({mouseGridPos.x, lastPos.y});
            }
            if (mouseGridPos != path.back())
            {
                addPoint(mouseGridPos);
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
    path.clear();
    visited.clear();
}