#include "Scene_Grid.h"
#include "GameEngine.hpp"
#include "Assets.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

Scene_Grid::Scene_Grid(GameEngine * game)
    : Scene(game)
{
    init();
}

void Scene_Grid::init()
{
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    m_viewController.zoomTo(m_game->window(), 8, { 0, 0 });
        
    m_font = Assets::Instance().getFont("Tech");
    m_text.setFont(m_font);
    m_text.setPosition({ 10, 5 });
    m_text.setCharacterSize(10);

    m_grid = Grid<int>(128, 128, 0);
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if ((i + j) % 2)
            {
                m_grid.set(i, j, 1);
            }
        }
    }

    m_gridColors.push_back(sf::Color(0, 0, 0));
    m_gridColors.push_back(sf::Color(255, 0, 0));
}

void Scene_Grid::onFrame()
{
    sUserInput();
    sGUI();
    sRender(); 
    m_currentFrame++;
}

void Scene_Grid::sUserInput()
{
    while (auto event = m_game->window().pollEvent())
    {
        ImGui::SFML::ProcessEvent(m_game->window(), *event);
        m_viewController.processEvent(m_game->window(), *event);

        if (event->is<sf::Event::Closed>())
        {
            std::exit(0);
        }

    }
}

void Scene_Grid::sGUI()
{
  
    ImGui::Begin("Scene Properties");

    if (ImGui::BeginTabBar("MyTabBar"))
    {
        if (ImGui::BeginTabItem("Debug"))
        {
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Animations"))
        {
            // STUDENT TODO
            ImGui::Text("Do this");

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Entity Manager"))
        {
            // STUDENT TODO
            ImGui::Text("Do this too");

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

// renders the scene
void Scene_Grid::sRender()
{
    const sf::Color gridColor(64, 64, 64);

    m_lineStrip.clear();
    m_quadArray.clear();

    // draw grid cells with the associated colors
    for (size_t x = 0; x < m_grid.width(); x++)
    {
        for (size_t y = 0; y < m_grid.height(); y++)
        {
            drawRect<float>(x * m_gridSize, y * m_gridSize, m_gridSize, m_gridSize, m_gridColors[m_grid.get(x, y)]);
        }
    }

    for (int x = 0; x <= int(m_grid.width()); x++)
    {
        drawLine<float>(x*m_gridSize, 0, x*m_gridSize, m_grid.height() * m_gridSize, gridColor);
    }

    for (int y = 0;  y <= int(m_grid.height()); y++)
    {
        drawLine<float>(0, y*m_gridSize, m_grid.width() * m_gridSize, y*m_gridSize, gridColor);
    }

    m_game->window().draw(m_quadArray);
    m_game->window().draw(m_lineStrip);
    m_game->window().draw(m_text);
}