#include "app.h"

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
        sf::RectangleShape rect({static_cast<float>(DEFAULT_TILE_HEIGHT), static_cast<float>(DEFAULT_TILE_WIDTH)});
        rect.setFillColor(sf::Color::Black);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1.f);
        _grid[i+j*COLUMNS].rect = rect;
        _grid[i+j*COLUMNS].entropy_value = 9; // Hard code for now
      }
    }
  }
  
  void App::drawGrid()
  {
    for (std::size_t j = 0; j < ROWS; j++)
    {
      for (std::size_t i = 0; i < COLUMNS; i++)
      {
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

  std::vector<sf::Sprite> App::getTiles()
  {
    static const sf::Texture spriteTexture("punyworld-overworld-tileset.png");
    std::vector<sf::Sprite> tiles{};

    for (int y = 0; y < spriteTexture.getSize().y; y += App::DEFAULT_TILE_HEIGHT)
    {
      for (int x = 0; x < spriteTexture.getSize().x; x += App::DEFAULT_TILE_WIDTH)
      {
        sf::Sprite st(spriteTexture);
        st.setTextureRect(
          sf::IntRect(
            {x, y},
            {
              App::DEFAULT_TILE_WIDTH,
              App::DEFAULT_TILE_HEIGHT
            }
          )
        );
        tiles.push_back(st);
      } 
    }

    return tiles;
  }

  void App::displayTiles()
  {
    /*
    // Temporary display solution
    float posx = 0, posy = 0;
    std::mt19937 mt{ std::random_device{}() };
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

      sf::Text entropy_text(font, std::to_string(_tiles[idx].entropy_value), 14);
      entropy_text.setPosition({posx, posy});
      // _tiles[idx].second.setPosition({posx, posy});
      _window->draw(entropy_text);
      posx += App::DEFAULT_TILE_HEIGHT;
    }*/
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
    
    _tiles.push_back(Tile{ .name = "grass", .entropy_value = 9, .sprite = &tiles[2] });
    _tiles.push_back(Tile{ .name = "top_left_edge_lake", .entropy_value = 9, .sprite = &tiles[277] });
    _tiles.push_back(Tile{ .name = "top_middle_edge_lake", .entropy_value = 9, .sprite = &tiles[278] });
    _tiles.push_back(Tile{ .name = "top_right_edge_lake", .entropy_value = 9, .sprite = &tiles[279] });
    _tiles.push_back(Tile{ .name = "left_mid_edge_lake", .entropy_value = 9, .sprite = &tiles[304] });
    _tiles.push_back(Tile{ .name = "mid_water", .entropy_value = 9, .sprite = &tiles[305] });
    _tiles.push_back(Tile{ .name = "right_mid_edge_lake", .entropy_value = 9, .sprite = &tiles[306] });
    _tiles.push_back(Tile{ .name = "bottom_left_edge_lake", .entropy_value = 9, .sprite = &tiles[331] });
    _tiles.push_back(Tile{ .name = "bottom_mid_edge_lake", .entropy_value = 9, .sprite = &tiles[332] });
    _tiles.push_back(Tile{ .name = "bottom_right_edge_lake", .entropy_value = 9, .sprite = &tiles[333] });
  }

};
