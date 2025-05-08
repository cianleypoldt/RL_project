#include "Renderer.h"
#include <cmath>

Drawable::Drawable(const sf::VertexArray& shape, sf::Vector2f initialPos)
    : m_vertexArray(shape) {
    m_transform.translate(initialPos);
}

void Drawable::setPos(sf::Vector2f newPos) {
    m_transform = sf::Transform();
    m_transform.translate(newPos);
}

void Drawable::setRot(float newRot) {
    m_transform.rotate(sf::degrees(newRot));
}

void Drawable::draw(sf::RenderTarget& target) const {
    target.draw(m_vertexArray, m_transform);
}

bool Drawable::contains(sf::Vector2f point) const {
    for (size_t i = 0; i < m_vertexArray.getVertexCount(); ++i) {
        sf::Vector2f transformedPoint = m_transform.transformPoint(m_vertexArray[i].position);
        if (std::hypot(point.x - transformedPoint.x, point.y - transformedPoint.y) < 2.0f) {
            return true;
        }
    }
    return false;
}

DrawableShape::DrawableShape(const sf::ConvexShape& shape, sf::Vector2f initialPos)
    : m_convexShape(shape) {
    m_transform.translate(initialPos);
}

void DrawableShape::setPos(sf::Vector2f newPos) {
    m_transform = sf::Transform();
    m_transform.translate(newPos);
}

void DrawableShape::setRot(float newRot) {
    m_transform.rotate(sf::degrees(newRot));
}

void DrawableShape::draw(sf::RenderTarget& target) const {
    sf::RenderStates states;
    states.transform = m_transform * m_convexShape.getTransform();
    target.draw(m_convexShape, states);
}

bool DrawableShape::contains(sf::Vector2f point) const {
    sf::Transform combined = m_transform * m_convexShape.getTransform();
    sf::Transform inverse = combined.getInverse();
    sf::Vector2f localPoint = inverse.transformPoint(point);

    std::size_t count = m_convexShape.getPointCount();
    bool inside = false;
    for (std::size_t i = 0, j = count - 1; i < count; j = i++) {
        sf::Vector2f pi = m_convexShape.getPoint(i);
        sf::Vector2f pj = m_convexShape.getPoint(j);
        if (((pi.y > localPoint.y) != (pj.y > localPoint.y)) &&
            (localPoint.x < (pj.x - pi.x) * (localPoint.y - pi.y) / (pj.y - pi.y) + pi.x)) {
            inside = !inside;
        }
    }
    return inside;
}

sf::ConvexShape& DrawableShape::convex()
{
    return m_convexShape;
}
