#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <iostream>
#include <cassert>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Assets
{
private:
    std::map<std::string, sf::Texture>     m_textureMap;
    std::map<std::string, sf::Font>        m_fontMap;
    std::map<std::string, sf::SoundBuffer> m_soundBufferMap;
    std::map<std::string, sf::Sound>       m_soundMap;

    Assets() = default;

public:
    static Assets& Instance()
    {
        static Assets instance;
        return instance;
    }

    // -------------------------------------------------------
    // Texture
    // uses explicit Texture(path) constructor in SFML 3.0 :contentReference[oaicite:0]{index=0}
    void addTexture(const std::string& name, const std::filesystem::path& path, bool smooth)
    {
        try
        {
            sf::Texture tex{ path };
            tex.setSmooth(smooth);
            m_textureMap.emplace(name, std::move(tex));
            std::cout << "Loaded Texture: " << path << "\n";
        }
        catch (const sf::Exception& e)
        {
            std::cerr << "Could not load texture file: " << path << " (" << e.what() << ")\n";
        }
    }

    // -------------------------------------------------------
    // Font
    // uses explicit Font(path) constructor in SFML 3.0 :contentReference[oaicite:1]{index=1}
    void addFont(const std::string& name, const std::filesystem::path& path)
    {
        try
        {
            sf::Font fnt{ path };
            m_fontMap.emplace(name, std::move(fnt));
            std::cout << "Loaded Font:    " << path << "\n";
        }
        catch (const sf::Exception& e)
        {
            std::cerr << "Could not load font file: " << path << " (" << e.what() << ")\n";
        }
    }

    // -------------------------------------------------------
    // Sound
    // uses explicit SoundBuffer(path) constructor in SFML 3.0 :contentReference[oaicite:2]{index=2}
    // and Sound(buffer) constructor :contentReference[oaicite:3]{index=3}
    void addSound(const std::string& name, const std::filesystem::path& path)
    {
        try
        {
            sf::SoundBuffer buf{ path };
            m_soundBufferMap.emplace(name, buf);

            sf::Sound snd{ buf };
            snd.setVolume(25);
            m_soundMap.emplace(name, std::move(snd));

            std::cout << "Loaded Sound:   " << path << "\n";
        }
        catch (const sf::Exception& e)
        {
            std::cerr << "Could not load sound file: " << path << " (" << e.what() << ")\n";
        }
    }

    // -------------------------------------------------------
    // Getters
    const sf::Texture& getTexture(const std::string& name) const
    {
        auto it = m_textureMap.find(name);
        assert(it != m_textureMap.end());
        return it->second;
    }

    const sf::Font& getFont(const std::string& name) const
    {
        auto it = m_fontMap.find(name);
        assert(it != m_fontMap.end());
        return it->second;
    }

    sf::Sound& getSound(const std::string& name)
    {
        auto it = m_soundMap.find(name);
        assert(it != m_soundMap.end());
        return it->second;
    }
};
