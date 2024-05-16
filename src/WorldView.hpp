#pragma once

#include <SFML/Graphics.hpp>

class WorldView
{
    sf::Vector2f    m_viewPos;          // the top-left (x, y) position of the view
    sf::Vector2f    m_viewSize;         // the size (width, height) of the view
    sf::Vector2f    m_viewCenter;       // the center (x, y) position of the view
    sf::Vector2f    m_savedViewPos;     // the top-left (x, y) position of the saved view
    sf::Vector2f    m_savedViewSize;    // the size (width, height) of the saved view
    sf::Vector2f    m_scrollAmount;     // the amount we should scroll on the next frame update
    sf::Vector2f    m_windowSize;       // the size of the SFML window
    sf::Vector2f    m_mouseWindowPos;   // position of the mouse on the SFML window
    sf::Vector2f    m_mouseWorldPos;    // position of the mouse in the SFML world
    sf::Vector2f    m_dragAmount;       // amount the mouse was physically dragged last frame

    bool    m_dragging = false;         // whether we are currently dragging the view

    bool    m_scrollMomentum = false;   // should the scroll have momentum (deceleration)
    float   m_scrollDecel = 0.9f;       // if so, what is the deceleration
    float   m_stopScrollSpeed = 4.0f;   // what speed should we hard-stop the momentum scroll

    int     m_scrollButton = sf::Mouse::Right;

    float length(sf::Vector2f v)
    {
        return sqrtf(v.x * v.x + v.y * v.y);
    }

public:

    WorldView() { }

    void update()
    {
        move(m_scrollAmount);
        m_scrollAmount *= (length(m_scrollAmount) >= m_stopScrollSpeed) ? m_scrollDecel : 0;
        if (!m_scrollMomentum) { m_scrollAmount = { 0, 0 }; }
    }

    void scroll(sf::Vector2f scroll)
    {
        m_scrollAmount = scroll;
    }
    
    void move(sf::Vector2f move)
    {
        m_viewPos += move;
        m_viewCenter += move;
    }

    sf::Vector2f windowToWorld(float x, float y)
    {
        sf::Vector2f ratio = { x / m_windowSize.x, y / m_windowSize.y };
        return { m_viewPos.x + ratio.x * m_viewSize.x, m_viewPos.y + ratio.y * m_viewSize.y };
    }

    sf::Vector2f windowToWorld(sf::Vector2f screen)
    {
        return windowToWorld(screen.x, screen.y);
    }

    void moveTo(sf::Vector2f moveTo)
    {
        m_viewPos = moveTo;
        m_viewCenter = m_viewPos + (m_viewSize / 2.0f);
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
        m_viewCenter = m_viewPos + (m_viewSize / 2.0f);
        stopScroll();
    }
    
    // zoom by a given amount, maintain center
    void zoom(float factor)
    {
        m_viewSize = m_viewSize * factor;
        m_viewCenter = m_viewPos + (m_viewSize / 2.0f);
    }

    // zoom to a target, it will remain fixed
    void zoomTo(float factor, sf::Vector2f target)
    {
        sf::Vector2f pRatio(target.x / m_windowSize.x, target.y / m_windowSize.y);
        sf::Vector2f oldPos = m_viewPos + sf::Vector2f(m_viewSize.x * pRatio.x, m_viewSize.y * pRatio.y);

        m_viewSize *= factor;
        m_viewPos = m_viewCenter - (m_viewSize / 2.0f);

        sf::Vector2f newPos = m_viewPos + sf::Vector2f(m_viewSize.x * pRatio.x, m_viewSize.y * pRatio.y);
        move(oldPos -newPos);
    }
    
    void setView(const sf::View& view)
    {
        m_viewCenter = view.getCenter();
        m_viewSize   = view.getSize();
        m_viewPos    = m_viewCenter - (m_viewSize / 2.0f);
    }

    void stopScroll()
    {
        m_scrollAmount = sf::Vector2f();
    }

    sf::View getSFMLView()
    {
        return sf::View(sf::FloatRect(m_viewPos.x, m_viewPos.y, m_viewSize.x, m_viewSize.y));
    }

    void processEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            // happens when the scroll button is pressed
            if (event.mouseButton.button == m_scrollButton)
            {
                m_dragging = true;
                m_dragAmount = sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
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
            float zoom = 1.0f - (0.2f * event.mouseWheel.delta);
            zoomTo(zoom, sf::Vector2f((float)event.mouseWheel.x, (float)event.mouseWheel.y));
        }

        // happens whenever the mouse is being moved
        if (event.type == sf::Event::MouseMoved)
        {
            m_mouseWindowPos = { (float)event.mouseMove.x, (float)event.mouseMove.y };
            m_mouseWorldPos = windowToWorld(m_mouseWindowPos);

            if (m_dragging)
            {
                auto prev = windowToWorld(m_dragAmount);
                auto curr = windowToWorld({ (float)event.mouseMove.x, (float)event.mouseMove.y });
                scroll(prev - curr);
                m_dragAmount = { (float)event.mouseMove.x, (float)event.mouseMove.y };
            }
        }
    }

    void setWindowSize(sf::Vector2u windowSize) { m_windowSize = sf::Vector2f((float)windowSize.x, (float)windowSize.y); }
    void setScrollButton(int button) { m_scrollButton = button; }
    void setScrollMomentum(bool momentum) { m_scrollMomentum = momentum; }

    sf::Vector2f pos() const { return m_viewPos; }
    sf::Vector2f center() const { return m_viewCenter; }
    sf::Vector2f size() const { return m_viewSize; }
    sf::Vector2f savedPos() const { return m_savedViewPos; }
    sf::Vector2f savedSize() const { return m_savedViewSize; }
};