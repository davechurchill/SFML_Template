#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class GameEngine;

class Scene
{

protected: 
    
    GameEngine *    m_game          = nullptr;
    bool            m_paused        = false;
    size_t          m_currentFrame  = 0;
    sf::VertexArray m_lineStrip     { sf::PrimitiveType::LineStrip };
    sf::VertexArray m_quadArray     { sf::PrimitiveType::Triangles };
    sf::VertexArray m_triangleStrip { sf::PrimitiveType::TriangleStrip };

    Scene(GameEngine* game)
    {
        m_game = game;
    }

public:

    virtual void onFrame() = 0;

    template <class T>
    void drawLine(T x1, T y1, T x2, T y2, sf::Color color)
    {
        sf::Vertex v1{ { float(x1), float(y1) }, color };
        sf::Vertex v2{ { float(x2), float(y2) }, color };

        if (m_lineStrip.getVertexCount() > 0)
        {
            m_lineStrip.append({ v1.position, sf::Color{0,0,0,0} });
        }

        m_lineStrip.append(v1);
        m_lineStrip.append(v2);
        m_lineStrip.append({ v2.position, sf::Color{0,0,0,0} });
    }


    template <class T>
    void drawRect(T x, T y, T w, T h, sf::Color color)
    {
        sf::Vertex v0{ { float(x),       float(y)     }, color };
        sf::Vertex v1{ { float(x + w),   float(y)     }, color };
        sf::Vertex v2{ { float(x + w),   float(y + h) }, color };
        sf::Vertex v3{ { float(x),       float(y + h) }, color };

        m_quadArray.append(v0);
        m_quadArray.append(v1);
        m_quadArray.append(v2);

        m_quadArray.append(v2);
        m_quadArray.append(v3);
        m_quadArray.append(v0);
    }
};