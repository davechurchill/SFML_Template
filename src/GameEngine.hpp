#pragma once

#include "Scene.hpp"
#include "Assets.hpp"

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{

protected:
    
    sf::RenderWindow    m_window;
    std::string         m_currentScene;
    SceneMap            m_sceneMap;
    size_t              m_simulationSpeed = 1;
    bool                m_running = true;
    sf::Clock           m_deltaClock;
    ImGuiStyle          m_originalStyle;

    void update()
    {
        ImGui::SFML::Update(m_window, m_deltaClock.restart());

        if (!isRunning()) { return; }

        if (m_sceneMap.empty()) { return; }

        m_window.clear();
        currentScene()->onFrame();
        ImGui::SFML::Render(m_window);
        m_window.display();
    }

    std::shared_ptr<Scene> currentScene()
    {
        return m_sceneMap.at(m_currentScene);
    }

public:
    
    GameEngine()
    {
        init();
    }

    void init()
    {
        m_window.create(sf::VideoMode({ 1600, 900 }), "Grid View");
        m_window.setFramerateLimit(60);

        ImGui::SFML::Init(m_window);
        m_originalStyle = ImGui::GetStyle();

        Assets::Instance().addFont("Tech", "fonts/tech.ttf");
    }

    void quit()
    {
        m_running = false;
    }

    void run()
    {
        while (isRunning())
        {
            update();
        }
    }

    unsigned int width() const
    {
        return m_window.getSize().x;
    }

    unsigned int height() const
    {
        return m_window.getSize().x;
    }

    sf::RenderWindow& window()
    {
        return m_window;
    }

    bool isRunning()
    {
        return m_running && m_window.isOpen();
    }

    template <class T>
    void changeScene(const std::string& sceneName, bool endCurrentScene = false)
    {
        m_window.setView(m_window.getDefaultView());
        ImGui::GetStyle() = m_originalStyle;

        if (m_sceneMap.find(sceneName) == m_sceneMap.end())
        {
            std::shared_ptr<Scene> scene = std::make_shared<T>(this);
            m_sceneMap[sceneName] = scene;
        }

        if (endCurrentScene)
        {
            m_sceneMap.erase(m_sceneMap.find(m_currentScene));
        }

        m_currentScene = sceneName;
    }
};