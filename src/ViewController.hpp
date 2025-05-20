#pragma once

#include <cassert>
#include <SFML/Graphics.hpp>

class ViewController
{
    sf::Vector2i        m_previousMousePos;
    sf::Mouse::Button   m_scrollButton = sf::Mouse::Button::Right;

public:

    ViewController()
    { 
    }

    void setScrollButton(sf::Mouse::Button button)
    {
        m_scrollButton = button;
    }

    // zoom the view by a specific factor
    // the 'target' position in world coordinates should remain fixed
    // by default, view.zoom() would keep the center of the view fixed
    void zoomTo(sf::RenderWindow& window, float factor, const sf::Vector2f& target)
    {
        sf::View view = window.getView();
        sf::Vector2f offset = (target - view.getCenter()) * factor;
        view.setCenter(target - offset);
        view.setSize(view.getSize() * factor);
        window.setView(view);
    }

    // process mouse events for scrolling and zooming
    // will modify the view of the window immediately
    void processEvent(sf::RenderWindow& window, const sf::Event& event)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (auto* mw = event.getIf<sf::Event::MouseWheelScrolled>(); mw)
        {
            float zoom = 1.0f - (0.2f * mw->delta);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
            zoomTo(window, zoom, worldPos);
        }

        if (auto* mm = event.getIf<sf::Event::MouseMoved>(); mm)
        {
            if (sf::Mouse::isButtonPressed(m_scrollButton))
            {
                sf::Vector2f prev = window.mapPixelToCoords(m_previousMousePos);
                sf::Vector2f curr = window.mapPixelToCoords(mousePos);
                sf::View view = window.getView();
                view.move(prev - curr);
                window.setView(view);
            }

            m_previousMousePos = mousePos;
        }
    }
};