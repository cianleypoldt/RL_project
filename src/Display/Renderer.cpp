#include "Renderer.h"
#include "../Utility/utilities.h"
#include <cmath>
#include <vector>

Renderer::Renderer(const RendererConfig& _config)
    : config(_config), settings(), m_window()
{
    settings.antiAliasingLevel = 8;

    m_window.create(sf::VideoMode(config.dimensions), config.title, sf::Style::None ,sf::State::Windowed, settings);
    m_window.setFramerateLimit(config.fpsLimit);
}

void Renderer::addBackgroundStatic(const sf::VertexArray& shape, sf::Vector2f pos) {
    BackgroundStatic bg{ shape, sf::Transform().translate(pos) };
    m_backgroundStatics.push_back(bg);
}

std::shared_ptr<Drawable> Renderer::addDrawable(const sf::VertexArray& shape, sf::Vector2f pos) {
    auto drawable = std::make_shared<Drawable>(shape, pos);
    m_drawables.push_back(drawable);
    return drawable;
}

std::shared_ptr<DrawableShape> Renderer::addCircle(sf::Vector2f pos, float radius, sf::Color color) {

    sf::ConvexShape shape;
    unsigned int point_count = (geometry::pi * radius) / (2 * 5);
    shape.setPointCount(point_count);
    for (size_t i = 0; i < point_count; ++i) {
        float angle = i * 2 * 3.14159265f / point_count;
        shape.setPoint(i, sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius));
    }
    shape.setFillColor(color);

    auto drawableShape = std::make_shared<DrawableShape>(shape, pos);
    m_drawables.push_back(drawableShape);
    return drawableShape;
}

std::shared_ptr<DrawableShape> Renderer::addRoundedRect(sf::Vector2f pos, sf::Vector2f dimentions, float corner_radius, sf::Color color)
{
    int point_count = (geometry::pi * corner_radius) / (2 * 5);
    sf::ConvexShape shape(point_count * 4);
    std::vector<sf::Vector2f> points = geometry::roundedBoxPArray(dimentions, corner_radius, point_count);
    for (int i = 0; i < points.size(); i++)
    {
        shape.setPoint(i, points[i]);
    }
    auto drawableShape = std::make_shared<DrawableShape>(shape, pos);
    m_drawables.push_back(drawableShape);
    return drawableShape;
}

void Renderer::removeDrawable(const std::shared_ptr<DrawableBase>& drawable) {
    //auto it = std::remove(m_drawables.begin(), m_drawables.end(), drawable);
    //m_drawables.erase(it, m_drawables.end());
}

void Renderer::clear() {
    m_window.clear();
}

void Renderer::display() {
    m_window.display();
}

void Renderer::render() {
    for (const auto& bg : m_backgroundStatics) {
        m_window.draw(bg.shape, bg.transform);
    }
    for (const auto& drawable : m_drawables) {
        drawable->draw(m_window);
    }
}

bool Renderer::isOpen() const {
    return m_window.isOpen();
}

void Renderer::pollEvents()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        m_window.close();
    }

    if (hovered())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
            m_window.close();
        }
    }

    if (selected)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            windowMove({ -20, 0 });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            windowMove({ 20, 0 });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            windowMove({ 0, -20 });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            windowMove({ 0, 20 });
        }
    }

}

sf::Vector2i Renderer::windowPos()
{
    const static sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    int newX = m_window.getPosition().x - desktop.size.x / 4;
    int newY = m_window.getPosition().y - desktop.size.y / 4;

    return sf::Vector2i(newX, newY).componentWiseMul({1,-1});
}

void Renderer::windowTo(sf::Vector2i newPos)
{
    const static sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    bool active = m_window.setActive(true);
    int newX = desktop.size.x / 4;
    int newY = desktop.size.y / 4;

    m_window.setPosition(sf::Vector2i(newX, newY) + newPos.componentWiseMul({ 1,-1 }));
}

void Renderer::windowMove(sf::Vector2i offset)
{
    m_window.setPosition(m_window.getPosition() + offset);
}

bool Renderer::hovered()
{
    sf::Vector2i localPos = sf::Mouse::getPosition(m_window);
    sf::Vector2u size = m_window.getSize();

    return (localPos.x >= 0 && localPos.x < (int)size.x && localPos.y >= 0 && localPos.y < (int)size.y);
}

std::shared_ptr<DrawableBase> Renderer::pickDrawableAt(sf::Vector2f point) {
    for (auto it = m_drawables.rbegin(); it != m_drawables.rend(); ++it) {
        if ((*it)->contains(point)) {
            return *it;
        }
    }
    return nullptr;
}
