#pragma once

#include "grafik.hpp"
#include <vector>
#include <SFML/System/Clock.hpp>

class gd_GIF;

namespace nada {

class Gif final : public Graphic {

public:

    explicit Gif(const std::string& datei);

    ~Gif();

    void draw(sf::RenderWindow* fenster) override;

private:

    void next_frame(bool force);

    void cache_frames();

private:

    sf::Clock gif_timer;

    gd_GIF* gif = nullptr;

    uint8_t* color = nullptr;

    unsigned frame_n = 0;

    std::vector<uint8_t> frame;

    std::vector<uint8_t> frame_rgba;

    std::vector<std::unique_ptr<sf::Texture>> frames;

};

} // namespace nada
