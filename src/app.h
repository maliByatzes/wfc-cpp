#ifndef app_h_
#define app_h_

#include <SFML/Graphics.hpp>
#include <utility>
#include <cassert>
#include <cstddef>
#include <random>

namespace wfc
{
    struct Tile {
        std::string name;
        int entropy_value;
        sf::Sprite *sprite;
    };
    
    class App
    {
    private:
        sf::RenderWindow *_window = nullptr;
        std::vector<Tile> _tiles; 

        std::vector<sf::Sprite> getTiles();
        void displayTiles();

    public:
        static const unsigned int DEFAULT_WIDTH;
        static const unsigned int DEFAULT_HEIGHT;
        static const unsigned int DEFAULT_TILE_WIDTH;
        static const unsigned int DEFAULT_TILE_HEIGHT;
        void setWindow(sf::RenderWindow *);
        sf::RenderWindow* getWindow();
        void setDesiredTiles();
        void run();

        App() = default;
        virtual ~App() = default;
    };
};

#endif
