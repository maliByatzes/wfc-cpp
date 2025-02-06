#include "app.h"
#include <SFML/Graphics.hpp>

using namespace wfc;

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({App::DEFAULT_WIDTH, App::DEFAULT_HEIGHT}),
        "WFC"
    );
    window.clear(sf::Color::Black);
    window.setFramerateLimit(120);
    auto _ = window.setActive(false);

    App app{};
    app.setWindow(&window);
    app.setDesiredTiles();

    app.run();

    return 0;
}
