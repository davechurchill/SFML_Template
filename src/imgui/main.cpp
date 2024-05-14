#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Window Title");
    ImGui::SFML::Init(window);

    bool circleExists = true;
    float circleRadius = 200.0f;
    int circleSegments = 100;
    float circleColor[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255 };
    char windowTitle[255] = "ImGui + SFML = <3";
    sf::CircleShape shape(circleRadius, circleSegments);
    shape.setFillColor(sf::Color
    (
        (int)(circleColor[0] * 255),
        (int)(circleColor[1] * 255),
        (int)(circleColor[2] * 255)
    )); // Color circle
    shape.setOrigin(circleRadius, circleRadius);
    shape.setPosition(400, 400); // Center circle

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::ShowDemoWindow();
        ImGui::Begin("Window title");
        ImGui::Text("Window text!");
        ImGui::Checkbox("Circle", &circleExists);
        ImGui::SliderFloat("Radius", &circleRadius, 100.0f, 300.0f);
        ImGui::SliderInt("Sides", &circleSegments, 3, 150);
        ImGui::ColorEdit3("Color Circle", circleColor);
        ImGui::InputText("Window title", windowTitle, 255);
        if (ImGui::Button("Update window title")) {
            window.setTitle(windowTitle);
        }
        ImGui::End();

        shape.setRadius(circleRadius);
        shape.setOrigin(circleRadius, circleRadius);
        shape.setPointCount(circleSegments);
        shape.setFillColor(sf::Color
        (
            (int)(circleColor[0] * 255),
            (int)(circleColor[1] * 255),
            (int)(circleColor[2] * 255)
        )); // Color circle

        window.clear(sf::Color(18, 33, 43)); // Color background
        if (circleExists)
            window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}