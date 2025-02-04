#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <vector>

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "WFC CPP");

    const sf::Texture spriteTexture("punyworld-overworld-tileset.png");

    const int tileWidth = 32;
    const int tileHeight = 32;

    std::vector<sf::Sprite> tiles;

    for (int y = 0; y < spriteTexture.getSize().y; y += tileHeight) {
        for (int x = 0; x < spriteTexture.getSize().x; x += tileWidth) {
            sf::Sprite tile(spriteTexture);
            tile.setTextureRect(sf::IntRect(sf::Vector2<int>{x, y}, sf::Vector2<int>{tileWidth, tileHeight}));
            tiles.push_back(tile);
        }
    }

    // Main loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        tiles[0].setPosition({100, 0});
        window.draw(tiles[0]);

        tiles[4].setPosition({200, 0});
        window.draw(tiles[4]);

        tiles[9].setPosition({300, 0});
        window.draw(tiles[9]);

        window.display();
    }

    return 0;
}
