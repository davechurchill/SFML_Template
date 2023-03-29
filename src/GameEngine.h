#pragma once

#include "Scene.h"
#include "Assets.h"

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{

protected:
    
    sf::RenderWindow    m_window;
    std::string         m_currentScene;
    SceneMap            m_sceneMap;
    size_t              m_simulationSpeed = 1;
    bool                m_running = true;

    void update();
    std::shared_ptr<Scene> currentScene();

public:
    
    GameEngine();

    void init();

    void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene = nullptr, bool endCurrentScene = false);

    void quit();
    void run();
    unsigned int width() const;
    unsigned int height() const;

    sf::RenderWindow & window();
    bool isRunning();
};