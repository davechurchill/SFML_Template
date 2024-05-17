#include "Scene_Grid.h"
#include "GameEngine.h"
#include "WorldView.hpp"
#include "Assets.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

Scene_Grid::Scene_Grid(GameEngine * game)
    : Scene(game)
    , m_viewController(game->window())
{
    init();
}

void Scene_Grid::init()
{
    m_viewController.zoomTo(8, { 0, 0 });
        
    m_font = Assets::Instance().getFont("Tech");
    m_text.setFont(m_font);
    m_text.setPosition(10, 5);
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
    //m_view.update();
    sUserInput();
    sGUI();
    sRender(); 
    m_currentFrame++;
}

void Scene_Grid::sUserInput()
{
    sf::Event event;
    while (m_game->window().pollEvent(event))
    {
        // this event triggers when the window is closed
        if (event.type == sf::Event::Closed)
        {
            m_game->quit();
        }

        ImGui::SFML::ProcessEvent(m_game->window(), event);
        m_viewController.processEvent(event);

        // this event is triggered when a key is pressed
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                {
                    m_game->changeScene("MENU", nullptr, true);
                    break;
                }
                case sf::Keyboard::G: m_drawGrid = !m_drawGrid; break;
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::W: break;
                case sf::Keyboard::A: break;
                case sf::Keyboard::S: break;
                case sf::Keyboard::D: break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) {}
            if (event.mouseButton.button == sf::Mouse::Right) {}
        }

        // happens when the mouse button is released
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)  { }
            if (event.mouseButton.button == sf::Mouse::Right) { }
        }

        // happens whenever the mouse is being moved
        if (event.type == sf::Event::MouseMoved)
        {
            m_mouseWindowPos = { event.mouseMove.x, event.mouseMove.y };
            sf::Vector2i pixelPos = sf::Mouse::getPosition(m_game->window());

            // record the grid cell that the mouse position is currently over
            m_mouseGrid = { floor(m_mouseWorldPos.x / m_gridSize) * m_gridSize, floor(m_mouseWorldPos.y / m_gridSize) * m_gridSize };
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
    float gs = (float)m_gridSize;
    //m_game->window().setView(m_view.getSFMLView());

    // draw grid cells with the associated colors
    for (size_t x = 0; x < m_grid.width(); x++)
    {
        for (size_t y = 0; y < m_grid.height(); y++)
        {
            drawRect<float>(x * m_gridSize, y * m_gridSize, m_gridSize, m_gridSize, m_gridColors[m_grid.get(x, y)]);
        }
    }
    for (int x = 0; m_drawGrid && x <= (int)m_grid.width(); x++)
    {
        drawLine<float>(x*m_gridSize, 0, x*m_gridSize, m_grid.height() * m_gridSize, gridColor);
    }

    for (int y = 0; m_drawGrid && y <= (int)m_grid.height(); y++)
    {
        drawLine<float>(0, y*m_gridSize, m_grid.width() * m_gridSize, y*m_gridSize, gridColor);
    }

    m_game->window().draw(m_quadArray);
    m_game->window().draw(m_lineStrip);
    //m_game->window().setView(m_game->window().getDefaultView());
    m_game->window().draw(m_text);
}