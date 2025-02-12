#include "app.h"
#include <stdexcept>

namespace wfc
{
  const unsigned int App::DEFAULT_WIDTH = 480;
  const unsigned int App::DEFAULT_HEIGHT = 320;
  const unsigned int App::DEFAULT_TILE_WIDTH = 16;
  const unsigned int App::DEFAULT_TILE_HEIGHT = 16;
  const unsigned int App::COLUMNS = DEFAULT_WIDTH / DEFAULT_TILE_WIDTH;
  const unsigned int App::ROWS = DEFAULT_HEIGHT / DEFAULT_TILE_HEIGHT;

  void App::setWindow(sf::RenderWindow *w)
  {
    _window = w;
  }

  void App::setGrid()
  {
    _grid.resize(COLUMNS * ROWS);

    for (std::size_t j = 0; j < ROWS; j++)
    {
      for (std::size_t i = 0; i < COLUMNS; i++)
      {
        sf::RectangleShape rect(
        {
          static_cast<float>(DEFAULT_TILE_HEIGHT),
          static_cast<float>(DEFAULT_TILE_WIDTH)
        });
        // rect.setFillColor(sf::Color::Black);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1.f);
        _grid[i+j*COLUMNS].rect = rect;
        _grid[i+j*COLUMNS].entropy_value = 9; // Hard code for now
      }
    }
  }
  
  void App::drawGrid()
  {
    std::mt19937 mt{ /* std::random_device{}() */ };
    std::uniform_int_distribution<std::size_t> rng{0, _desiredTiles.size() - 1};

    for (std::size_t j = 0; j < ROWS; j++)
    {
      for (std::size_t i = 0; i < COLUMNS; i++)
      {

        _grid[i+j*COLUMNS].rect.setTexture(&_desiredTiles[0].sprite.getTexture());
        _grid[i+j*COLUMNS].rect.setPosition(
          {
            static_cast<float>(i * DEFAULT_TILE_WIDTH),
            static_cast<float>(j * DEFAULT_TILE_HEIGHT)
          });
        _window->draw(_grid[i+j*COLUMNS].rect);
      }
    }
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
      drawGrid();
      _window->display();
    }
  }

  void App::loadTileset()
  {
    if (!_tilesetTexture.loadFromFile("punyworld-overworld-tileset.png"))
    {
      throw std::runtime_error("Failed to load tileset texture.");
    }

    for (int y = 0; y < _tilesetTexture.getSize().y; y += DEFAULT_TILE_HEIGHT)
    {
      for (int x = 0; x < _tilesetTexture.getSize().x; x += DEFAULT_TILE_WIDTH)
      {
        sf::Sprite sprite(_tilesetTexture);
        sprite.setTextureRect(
          sf::IntRect(
            {x, y},
            {DEFAULT_TILE_WIDTH, DEFAULT_TILE_HEIGHT}
          )
        );
        _tiles.push_back(sprite);
      }
    }
  }
    
  void App::setDesiredTiles()
  {
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

    assert(_tiles.size() >= 10);
    
    _desiredTiles.push_back(Tile{ .name = "grass", .sprite = _tiles[2] });
    _desiredTiles.push_back(Tile{ .name = "top_left_edge_lake", .sprite = _tiles[277] });
    _desiredTiles.push_back(Tile{ .name = "top_middle_edge_lake", .sprite = _tiles[278] });
    _desiredTiles.push_back(Tile{ .name = "top_right_edge_lake", .sprite = _tiles[279] });
    _desiredTiles.push_back(Tile{ .name = "left_mid_edge_lake", .sprite = _tiles[304] });
    _desiredTiles.push_back(Tile{ .name = "mid_water", .sprite = _tiles[305] });
    _desiredTiles.push_back(Tile{ .name = "right_mid_edge_lake", .sprite = _tiles[306] });
    _desiredTiles.push_back(Tile{ .name = "bottom_left_edge_lake", .sprite = _tiles[331] });
    _desiredTiles.push_back(Tile{ .name = "bottom_mid_edge_lake", .sprite = _tiles[332] });
    _desiredTiles.push_back(Tile{ .name = "bottom_right_edge_lake", .sprite = _tiles[333] });
  }

};
