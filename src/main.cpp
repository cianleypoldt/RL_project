#include "Display/Renderer.h"
//#include "Utility/utilities.h"

int main()
{
    std::vector<std::unique_ptr<Renderer>> windows;
    {
        RendererConfig main_render_config{ {1000,500}, "main window", 60, sf::Style::None };
        windows.emplace_back(std::make_unique<Renderer>(main_render_config));
        RendererConfig debug_render_config{ {1000,500}, "debug window", 60, sf::Style::None };
        windows.emplace_back(std::make_unique<Renderer>(debug_render_config));
    }

    windows[0]->windowTo({420, 260});
    windows[1]->windowTo({420, -260});

    windows[0]->select();

    auto circle = windows[0]->addCircle({500,250}, 200, sf::Color::White);
    auto rect = windows[1]->addRoundedRect({ 500, 250 }, {400, 200}, 50, sf::Color::Transparent);

    circle->convex().setOutlineColor(sf::Color::Blue);
    circle->convex().setOutlineThickness(5);
    circle->convex().setFillColor(sf::Color::Transparent);

    rect->convex().setOutlineColor(sf::Color::Blue);
    rect->convex().setOutlineThickness(5);
    rect->convex().setFillColor(sf::Color::Yellow);

    while (!windows.empty())
    {
        for (auto it = windows.begin(); it != windows.end();)
        {
            it->get()->pollEvents();
            if (!(*it)->isOpen())
            {
                it = windows.erase(it);
            }
            else
            {
                it++;
            }
        }

        for (auto& window : windows)
        {
            window->clear();
            window->render();
            window->display();
        }
    }
}
