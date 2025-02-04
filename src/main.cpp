#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <vector>

void displayTiles(sf::RenderWindow& window, std::vector<sf::Sprite>& tiles) {
    float posx = 0, posy = 0;
    for (auto tile : tiles) {
        if (posx == 800) {
            posx = 0;
            posy += 32;
        }            
        
        tile.setPosition({posx, posy});
        window.draw(tile);
        posx += 32;
    }    
}

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

        displayTiles(window, tiles);

        window.display();
    }

    return 0;
}
