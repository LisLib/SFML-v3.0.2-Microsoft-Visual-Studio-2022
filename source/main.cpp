#include <SFML/Graphics.hpp>
#include <cstdlib>

int main()
{
    sf::RenderWindow window(sf::VideoMode({600, 600}),
                            "SFML Stencil",
                            sf::Style::Titlebar | sf::Style::Close,
                            sf::State::Windowed,
                            sf::ContextSettings{0 /* depthBits */, 8 /* stencilBits */});

    window.setVerticalSyncEnabled(true);

    sf::RectangleShape red({500, 50});
    red.setFillColor(sf::Color::Red);
    red.setPosition({270, 70});
    red.setRotation(sf::degrees(60));

    sf::RectangleShape green({500, 50});
    green.setFillColor(sf::Color::Green);
    green.setPosition({370, 100});
    green.setRotation(sf::degrees(120));

    sf::RectangleShape blue({500, 50});
    blue.setFillColor(sf::Color::Blue);
    blue.setPosition({550, 470});
    blue.setRotation(sf::degrees(180));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                break;
            }
        }

        window.clear(sf::Color::Black, 0);

        window.draw(red,
                    sf::StencilMode{sf::StencilComparison::Always, sf::StencilUpdateOperation::Replace, 3, ~0u, false});

        window.draw(green,
                    sf::StencilMode{sf::StencilComparison::Always, sf::StencilUpdateOperation::Replace, 1, ~0u, false});

        window.draw(blue,
                    sf::StencilMode{sf::StencilComparison::Greater, sf::StencilUpdateOperation::Replace, 2, ~0u, false});

        window.display();
    }

    return EXIT_SUCCESS;
}
