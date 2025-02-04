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
            posy += 16;
        }            
        
        tile.setPosition({posx, posy});
        window.draw(tile);
        posx += 16;
    }    
}

std::vector<sf::Sprite> getDesiredTiles(const std::vector<sf::Sprite>& tiles) {
    std::vector<sf::Sprite> desired_tiles{};

/*
    Tiles to use:
    - grass => 2
    - top-right edge lake => 279
    - top-middle edge lake => 278
    - top-left edge lake => 277
    - left mid edge lake => 304
    - mid water => 305
    - right mid edge lake => 306
    - bottom-left edge lake => 331
    - bottom-mid edge lake => 332
    - bottom-right edge lake => 333
*/

    desired_tiles.push_back(tiles[2]);
    desired_tiles.push_back(tiles[277]);
    desired_tiles.push_back(tiles[278]);
    desired_tiles.push_back(tiles[279]);
    desired_tiles.push_back(tiles[304]);
    desired_tiles.push_back(tiles[305]);
    desired_tiles.push_back(tiles[306]);
    desired_tiles.push_back(tiles[331]);
    desired_tiles.push_back(tiles[332]);
    desired_tiles.push_back(tiles[333]);
        
    return desired_tiles;
}

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "WFC CPP");

    const sf::Texture spriteTexture("punyworld-overworld-tileset.png");

    const int tileWidth = 16;
    const int tileHeight = 16;

    std::vector<sf::Sprite> tiles;

    for (int y = 0; y < spriteTexture.getSize().y; y += tileHeight) {
        for (int x = 0; x < spriteTexture.getSize().x; x += tileWidth) {
            sf::Sprite tile(spriteTexture);
            tile.setTextureRect(sf::IntRect(sf::Vector2<int>{x, y}, sf::Vector2<int>{tileWidth, tileHeight}));
            tiles.push_back(tile);
        }
    }

    std::vector<sf::Sprite> desired_tiles{ getDesiredTiles(tiles) };

    // Main loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        displayTiles(window, desired_tiles);

        window.display();
    }

    return 0;
}
