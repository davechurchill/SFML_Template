#pragma once

#include <cassert>
#include <SFML/Graphics.hpp>

class ViewController
{
    sf::RenderWindow &  m_window;
    sf::Vector2i        m_previousMousePos;
    sf::Mouse::Button   m_scrollButton = sf::Mouse::Right;

public:

    ViewController(sf::RenderWindow& window)
        : m_window(window)
    { 
    }

    void setScrollButton(sf::Mouse::Button button)
    {
        m_scrollButton = button;
    }

    // zoom the view by a specific factor
    // the 'target' position in world coordinates should remain fixed
    // by default, view.zoom() would keep the center of the view fixed
    void zoomTo(float factor, const sf::Vector2f& target)
    {
        sf::View view = m_window.getView();
        sf::Vector2f offset = (target - view.getCenter()) * factor;
        view.setCenter(target - offset);
        view.setSize(view.getSize() * factor);
        m_window.setView(view);
    }

    // process mouse events for scrolling and zooming
    // will modify the view of the window immediately
    void processEvent(const sf::Event& event)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

        if (event.type == sf::Event::MouseWheelScrolled)
        {
            float zoom = 1.0f - (0.2f * event.mouseWheelScroll.delta);
            sf::Vector2f worldPos = m_window.mapPixelToCoords(mousePos);
            zoomTo(zoom, worldPos);
        }

        if (event.type == sf::Event::MouseMoved)
        {
            if (sf::Mouse::isButtonPressed(m_scrollButton))
            {
                sf::Vector2f prev = m_window.mapPixelToCoords(m_previousMousePos);
                sf::Vector2f curr = m_window.mapPixelToCoords(mousePos);
                sf::View view = m_window.getView();
                view.move(prev - curr);
                m_window.setView(view);
            }

            m_previousMousePos = mousePos;
        }
    }
};