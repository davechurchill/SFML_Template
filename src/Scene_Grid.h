#pragma once

#include "Scene.h"
#include "WorldView.hpp"
#include "Grid.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Scene_Grid : public Scene
{   
    sf::Font            m_font;             
    sf::Text            m_text;

    float               m_gridSize = 32;
    bool                m_drawGrid = true;


    Grid<int>           m_grid;
    std::vector<sf::Color> m_gridColors;

    Vec2                m_dragAmount = { -1, -1 };
    Vec2                m_mouseWindowPos;
    Vec2                m_mouseWorldPos;
    Vec2                m_mouseGrid;
    
    WorldView           m_view;
    
    void init();  

    void sGUI();
    void sUserInput();  
    void sRender();
    
public:

    Scene_Grid(GameEngine * game);

    void onFrame();
};
