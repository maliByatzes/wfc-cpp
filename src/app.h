#ifndef app_h_
#define app_h_

#include <SFML/Graphics.hpp>
#include <utility>

namespace wfc
{
    class App
    {
    private:
        sf::RenderWindow *_window = nullptr;
        std::vector<sf::Sprite> _tiles; 
        std::vector<std::pair<int, sf::Sprite>> _grid;

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
        virtual ~App();
    };
};

#endif
