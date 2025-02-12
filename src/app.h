#ifndef app_h_
#define app_h_

#include <SFML/Graphics.hpp>
#include <unordered_map>
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

    struct Box {
        int entropy_value;
        sf::RectangleShape rect;
    };

    // Rule set on what can appear on each direction of the certain tile
    // [NORTH, EAST, SOUTH, WEST]
    inline std::unordered_map<std::string, std::vector<std::string>> ruleSet =
    {
        { "grass", {"grass", "grass", "grass", "grass"} },
        { "top_left_edge_lake", {"grass", "top_middle_edge_lake", "left_mid_edge_lake", "grass"} },   
        { "top_middle_edge_lake", {"grass", "top_middle_edge_lake", "mid_water", "top_left_edge_lake"} },   
        { "top_right_edge_lake", {"grass", "grass", "right_mid_edge_lake", "top_middle_edge_lake"} },
        { "left_mid_edge_lake", {"top_left_edge_lake", "mid_water", "bottom_left_edge_lake", "grass"} },
        { "mid_water", {"mid_water", "mid_water", "mid_water", "mid_water"} },   
        { "right_mid_edge_lake", {"top_right_edge_lake", "grass", "bottom_right_edge_lake", "mid_water"} },   
        { "bottom_left_edge_lake", {"left_mid_edge_lake", "bottom_mid_edge_lake", "grass", "grass"} },
        { "bottom_mid_edge_lake", {"mid_water", "bottom_right_edge_lake", "grass", "bottom_left_edge_lake"} },
        { "bottom_right_edge_lake", {"right_mid_edge_lake", "grass", "grass", "bottom_mid_edge_lake"} }
    };
    
    class App
    {
    private:
        sf::RenderWindow *_window = nullptr;
        std::vector<Box> _grid;
        std::vector<Tile> _tiles; 

        std::vector<sf::Sprite> getTiles();
        void displayTiles();

    public:
        static const unsigned int DEFAULT_WIDTH;
        static const unsigned int DEFAULT_HEIGHT;
        static const unsigned int DEFAULT_TILE_WIDTH;
        static const unsigned int DEFAULT_TILE_HEIGHT;
        static const unsigned int COLUMNS;
        static const unsigned int ROWS;
        void setWindow(sf::RenderWindow *);
        sf::RenderWindow* getWindow();
        void setGrid();
        void drawGrid();
        void setDesiredTiles();
        void run();

        App() = default;
        virtual ~App() = default;
    };
};

#endif
