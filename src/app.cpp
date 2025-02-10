#include "app.h"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <random>

namespace wfc
{
  const unsigned int App::DEFAULT_WIDTH = 480;
  const unsigned int App::DEFAULT_HEIGHT = 320;
  const unsigned int App::DEFAULT_TILE_WIDTH = 16;
  const unsigned int App::DEFAULT_TILE_HEIGHT = 16;

  void App::setWindow(sf::RenderWindow *w)
  {
    _window = w;
  }

  sf::RenderWindow* App::getWindow()
  {
    return _window;
  }

  void App::run()
  {
    auto _ = _window->setActive(false);
    while (_window->isOpen())
    {
      while (const std::optional event = _window->pollEvent())
      {
        if (event->is<sf::Event::Closed>())
          _window->close();
      }

      _window->clear();
      displayTiles();
      _window->display();
    }
  }

  std::vector<sf::Sprite> App::getTiles()
  {
    static const sf::Texture spriteTexture("punyworld-overworld-tileset.png");
    std::vector<sf::Sprite> tiles{};

    for (int y = 0; y < spriteTexture.getSize().y; y += App::DEFAULT_TILE_HEIGHT)
    {
      for (int x = 0; x < spriteTexture.getSize().x; x += App::DEFAULT_TILE_WIDTH)
      {
        sf::Sprite tile(spriteTexture);
        tile.setTextureRect(
          sf::IntRect(
            {x, y},
            {
              App::DEFAULT_TILE_WIDTH,
              App::DEFAULT_TILE_WIDTH
            }
          )
        );
        tiles.push_back(tile);
      } 
    }

    return tiles;
  }

  void App::displayTiles()
  { 
    // Temporary display solution
    float posx = 0, posy = 0;
    std::mt19937 mt{};
    std::uniform_int_distribution<std::size_t> rng{0, _tiles.size()};

    for (;;)
    {
      std::size_t idx = rng(mt);
      if (posx == App::DEFAULT_WIDTH)
      {
        posx = 0;
        posy += App::DEFAULT_TILE_HEIGHT;  
      }

      if (posy == App::DEFAULT_HEIGHT)
        break;

      _tiles[idx].setPosition({posx, posy});
      _window->draw(_tiles[idx]);
      posx += App::DEFAULT_TILE_HEIGHT;
    }
  }
  
  void App::setDesiredTiles()
  {
    std::vector<sf::Sprite> tiles{ App::getTiles() };
/**
 *Tiles to use:
 * - grass => 2
 * - top-right edge lake => 279
 * - top-middle edge lake => 278
 * - top-left edge lake => 277
 * - left mid edge lake => 304
 * - mid water => 305
 * - right mid edge lake => 306
 * - bottom-left edge lake => 331
 * - bottom-mid edge lake => 332
 * - bottom-right edge lake => 333
**/

    assert(tiles.size() >= 10);
    
    _tiles.push_back(tiles[2]);
    _tiles.push_back(tiles[277]);
    _tiles.push_back(tiles[278]);
    _tiles.push_back(tiles[279]);
    _tiles.push_back(tiles[304]);
    _tiles.push_back(tiles[305]);
    _tiles.push_back(tiles[306]);
    _tiles.push_back(tiles[331]);
    _tiles.push_back(tiles[332]);
    _tiles.push_back(tiles[333]);
  }

};
