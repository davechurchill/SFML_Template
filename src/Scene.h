#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class GameEngine;

class Scene
{

protected: 
    
    GameEngine *    m_game = nullptr;
    bool            m_paused = false;
    size_t          m_currentFrame = 0;
    sf::VertexArray m_lineStrip;
    sf::VertexArray m_quadArray;
    sf::VertexArray m_triangleStrip;

    Scene(GameEngine * game);

public:

    virtual void onFrame() = 0;

    template <class T>
    void drawLine(T x1, T y1, T x2, T y2, sf::Color color)
    {
        sf::Vertex v1(sf::Vector2f(static_cast<float>(x1), static_cast<float>(y1)), color);
        sf::Vertex v2(sf::Vector2f(static_cast<float>(x2), static_cast<float>(y2)), color);

        if (m_lineStrip.getVertexCount() > 0)
        {
            m_lineStrip.append(sf::Vertex(v1.position, sf::Color(0, 0, 0, 0)));
        }

        m_lineStrip.append(v1);
        m_lineStrip.append(v2);
        m_lineStrip.append(sf::Vertex(v2.position, sf::Color(0, 0, 0, 0)));
    }

    template <class T>
    void drawRect(T x, T y, T w, T h, sf::Color color)
    {
        m_quadArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(x),     static_cast<float>(y)),     color));
        m_quadArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(x + w), static_cast<float>(y)),     color));
        m_quadArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(x + w), static_cast<float>(y + h)), color));
        m_quadArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(x),     static_cast<float>(y + h)), color));
    }
};