#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

struct RendererConfig {
    sf::Vector2u dimensions = {1000, 500};
    std::string title = "Renderer";
    unsigned int fpsLimit = 60;
    unsigned int style = sf::Style::Default;
    sf::Vector2i position = {0,0};
};

struct BackgroundStatic {
    sf::VertexArray shape;
    sf::Transform transform;
};

class DrawableBase {
public:
    virtual void draw(sf::RenderTarget& target) const = 0;
    virtual void setPos(sf::Vector2f newPos) = 0;
    virtual void setRot(float newRot) = 0;
    virtual bool contains(sf::Vector2f point) const = 0;
    virtual ~DrawableBase() = default;
};

class Drawable : public DrawableBase {
private:
    sf::VertexArray m_vertexArray;
    sf::Transform m_transform;

public:
    Drawable(const sf::VertexArray& shape, sf::Vector2f initialPos);

    void setPos(sf::Vector2f newPos) override;
    void setRot(float newRot) override;
    void draw(sf::RenderTarget& target) const override;
    bool contains(sf::Vector2f point) const override;
};

class DrawableShape : public DrawableBase {
private:
    sf::ConvexShape m_convexShape;
    sf::Transform m_transform;

public:
    DrawableShape(const sf::ConvexShape& shape, sf::Vector2f initialPos);

    void setPos(sf::Vector2f newPos) override;
    void setRot(float newRot) override;
    void draw(sf::RenderTarget& target) const override;
    bool contains(sf::Vector2f point) const override;
    sf::ConvexShape& convex();
};

class Renderer {
private:

    RendererConfig config;
    sf::ContextSettings settings;
    sf::RenderWindow m_window;
    std::vector<BackgroundStatic> m_backgroundStatics;
    std::vector<std::shared_ptr<DrawableBase>> m_drawables;

    bool selected = false;


public:
    Renderer(const RendererConfig& config);

    void addBackgroundStatic(const sf::VertexArray& shape, sf::Vector2f pos);
    std::shared_ptr<Drawable> addDrawable(const sf::VertexArray& shape, sf::Vector2f pos);
    std::shared_ptr<DrawableShape> addCircle(sf::Vector2f pos, float radius, sf::Color color);
    std::shared_ptr<DrawableShape> addRoundedRect(sf::Vector2f pos, sf::Vector2f dimentions, float corner_radius, sf::Color color);

    void removeDrawable(const std::shared_ptr<DrawableBase>& drawable);

    void clear();
    void display();
    void render();
    bool isOpen() const;
    void pollEvents();
    sf::Vector2i windowPos();
    void windowTo(sf::Vector2i);
    void windowMove(sf::Vector2i);
    void select() { selected = true; }
    void deselect() { selected = false; }
    bool hovered();

    std::shared_ptr<DrawableBase> pickDrawableAt(sf::Vector2f point);
};
