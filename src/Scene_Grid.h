#pragma once

#include "Scene.hpp"
#include "ViewController.hpp"
#include "Grid.hpp"
#include "Vec2.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Scene_Grid : public Scene
{   
    sf::Font            m_font;             
    sf::Text            m_text{ m_font };

    float               m_gridSize = 32;

    Grid<int>           m_grid;
    std::vector<sf::Color> m_gridColors;
        
    ViewController      m_viewController;
    
    void init();  

    void sGUI();
    void sUserInput();  
    void sRender();
    
public:

    Scene_Grid(GameEngine * game);

    void onFrame();
};
