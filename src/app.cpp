#include "app.h"
#include <iostream>
#include <string>
#include <utility>

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
    std::mt19937 mt{ /* std::random_device{}() */ };
    std::uniform_int_distribution<std::size_t> rng{0, _tiles.size() - 1};
    const sf::Font font("IosevkaTermNerdFont-Medium.ttf");

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

      sf::Text entropy_text(font, std::to_string(_tiles[idx].first), 12);
      entropy_text.setPosition({posx, posy});
      // _tiles[idx].second.setPosition({posx, posy});
      _window->draw(entropy_text);
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
    
    _tiles.push_back(std::make_pair(9, tiles[2]));
    _tiles.push_back(std::make_pair(9, tiles[277]));
    _tiles.push_back(std::make_pair(9, tiles[278]));
    _tiles.push_back(std::make_pair(9, tiles[279]));
    _tiles.push_back(std::make_pair(9, tiles[304]));
    _tiles.push_back(std::make_pair(9, tiles[305]));
    _tiles.push_back(std::make_pair(9, tiles[306]));
    _tiles.push_back(std::make_pair(9, tiles[331]));
    _tiles.push_back(std::make_pair(9, tiles[332]));
    _tiles.push_back(std::make_pair(9, tiles[333]));
  }

};
