#include "Scene.h"
#include "GameEngine.h"

Scene::Scene(GameEngine * game)
    : m_game(game)
    , m_lineStrip(sf::LinesStrip)
    , m_quadArray(sf::Quads)
{ 
    
}
