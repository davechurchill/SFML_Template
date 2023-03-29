#include "GameEngine.h"
#include "Assets.h"

#include <iostream>

GameEngine::GameEngine()
{
    init();
}

void GameEngine::init()
{
    m_window.create(sf::VideoMode(1600, 900), "Grid View");
    m_window.setFramerateLimit(60);

    Assets::Instance().addFont("Tech", "fonts/tech.ttf");
}

bool GameEngine::isRunning()
{ 
    return m_running && m_window.isOpen();
}

sf::RenderWindow & GameEngine::window()
{
    return m_window;
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
    if (scene)
    {
        m_sceneMap[sceneName] = scene;
    }
    else
    {
        if (m_sceneMap.find(sceneName) == m_sceneMap.end())
        {
            std::cerr << "Warning: Scene does not exist: " << sceneName << std::endl;
            return;
        }
    }

    if (endCurrentScene)
    {
        m_sceneMap.erase(m_sceneMap.find(m_currentScene));
    }

    m_currentScene = sceneName;
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_sceneMap.at(m_currentScene);
}

void GameEngine::update()
{
    if (!isRunning()) { return; }

    if (m_sceneMap.empty()) { return; }

    currentScene()->onFrame();
}

void GameEngine::run()
{
    while (isRunning())
    {
        update();
    }
}

void GameEngine::quit()
{
    m_running = false;
}

unsigned int GameEngine::width() const
{
    return m_window.getSize().x;
}

unsigned int GameEngine::height() const
{
    return m_window.getSize().x;
}