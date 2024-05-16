#pragma once

#include "Vec2.hpp"
#include <SFML/Graphics.hpp>

class WorldView
{
    Vec2    m_viewPos;                  // the top-left (x, y) position of the view
    Vec2    m_viewSize;                 // the size (width, height) of the view
    Vec2    m_viewCenter;               // the center (x, y) position of the view
    Vec2    m_savedViewPos;             // the top-left (x, y) position of the saved view
    Vec2    m_savedViewSize;            // the size (width, height) of the saved view
    Vec2    m_scrollAmount;             // the amount we should scroll on the next frame update
    Vec2    m_windowSize;               // the size of the SFML window
    Vec2    m_mouseWindowPos;           // position of the mouse on the SFML window
    Vec2    m_mouseWorldPos;            // position of the mouse in the SFML world
    Vec2    m_dragAmount;               // amount the mouse was physically dragged last frame

    bool    m_dragging = false;         // whether we are currently dragging the view

    bool    m_scrollMomentum = false;   // should the scroll have momentum (deceleration)
    float   m_scrollDecel = 0.9f;       // if so, what is the deceleration
    float   m_stopScrollSpeed = 4.0f;   // what speed should we hard-stop the momentum scroll

    int     m_scrollButton = sf::Mouse::Right;

public:

    WorldView() { }

    void update()
    {
        move(m_scrollAmount);
        m_scrollAmount *= (m_scrollAmount.length() >= m_stopScrollSpeed) ? m_scrollDecel : 0;
        if (!m_scrollMomentum) { m_scrollAmount = { 0, 0 }; }
    }

    void scroll(Vec2 scroll)
    {
        m_scrollAmount = scroll;
    }
    
    void move(Vec2 move)
    {
        m_viewPos += move;
        m_viewCenter += move;
    }

    Vec2 windowToWorld(Vec2 screen)
    {
        Vec2 ratio = { screen.x / m_windowSize.x, screen.y / m_windowSize.y };
        return { m_viewPos.x + ratio.x * m_viewSize.x, m_viewPos.y + ratio.y * m_viewSize.y };
    }

    void moveTo(Vec2 moveTo)
    {
        m_viewPos = moveTo;
        m_viewCenter = m_viewPos + m_viewSize / 2;
    }

    void saveView()
    {
        m_savedViewPos = m_viewPos;
        m_savedViewSize = m_viewSize;
    }

    void loadView()
    {
        m_viewPos = m_savedViewPos;
        m_viewSize = m_savedViewSize;
        m_viewCenter = m_viewPos + m_viewSize / 2;
        stopScroll();
    }
    
    // zoom by a given amount, maintain center
    void zoom(double factor)
    {
        m_viewSize *= factor;
        m_viewPos   = m_viewCenter - m_viewSize / 2;
    }

    // zoom to a target, it will remain fixed
    void zoomTo(double factor, Vec2 target)
    {
        Vec2 pRatio = target / m_windowSize;
        Vec2 oldPos = m_viewPos + m_viewSize * pRatio;

        m_viewSize *= factor;
        m_viewPos = m_viewCenter - m_viewSize / 2;

        Vec2 newPos = m_viewPos + m_viewSize * pRatio;
        move(oldPos -newPos);
    }
    
    void setView(const sf::View& view)
    {
        m_viewCenter = { view.getCenter().x, view.getCenter().y };
        m_viewSize   = { view.getSize().x, view.getSize().y };
        m_viewPos    = m_viewCenter - m_viewSize / 2;
    }

    void stopScroll()
    {
        m_scrollAmount = Vec2();
    }

    sf::View getSFMLView()
    {
        return sf::View(sf::FloatRect((float)m_viewPos.x, (float)m_viewPos.y, (float)m_viewSize.x, (float)m_viewSize.y));
    }

    void processEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            // happens when the scroll button is pressed
            if (event.mouseButton.button == m_scrollButton)
            {
                m_dragging = true;
                m_dragAmount = { event.mouseButton.x, event.mouseButton.y };
                stopScroll();
            }
        }

        // happens when the mouse button is released
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == m_scrollButton) { m_dragging = false; }
        }

        if (event.type == sf::Event::MouseWheelMoved)
        {
            double zoom = 1.0 - (0.2 * event.mouseWheel.delta);
            zoomTo(zoom, Vec2(event.mouseWheel.x, event.mouseWheel.y));
        }

        // happens whenever the mouse is being moved
        if (event.type == sf::Event::MouseMoved)
        {
            m_mouseWindowPos = { event.mouseMove.x, event.mouseMove.y };
            m_mouseWorldPos = windowToWorld(m_mouseWindowPos);

            if (m_dragging)
            {
                auto prev = windowToWorld(m_dragAmount);
                auto curr = windowToWorld({ event.mouseMove.x, event.mouseMove.y });
                scroll(prev - curr);
                m_dragAmount = { event.mouseMove.x, event.mouseMove.y };
            }
        }
    }

    void setWindowSize(Vec2 windowSize) { m_windowSize = windowSize; }
    void setScrollButton(int button) { m_scrollButton = button; }
    void setScrollMomentum(bool momentum) { m_scrollMomentum = momentum; }

    const Vec2& pos() const { return m_viewPos; }
    const Vec2& center() const { return m_viewCenter; }
    const Vec2& size() const { return m_viewSize; }
    const Vec2& savedPos() const { return m_savedViewPos; }
    const Vec2& savedSize() const { return m_savedViewSize; }
};