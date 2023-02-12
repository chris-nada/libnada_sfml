#include <memory>
#include <nada/gif.hpp>
#include "thirdparty/gifdec.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace nada;

Gif::Gif(const std::string& datei) : Graphic() {
    // Elternkorrekturen
    is_shared = false;
    is_flipped = false;
    textur_pfad = datei;

    // Gif laden
    gif = gd_open_gif(datei.c_str());
    if (!gif) return;

    // Gif Frame laden
    frame.resize(gif->width * gif->height * 3);
    frame_rgba.resize(gif->width * gif->height * 4);

    color = &gif->gct.colors[gif->bgindex * 3];
    cache_frames(); // cache all frames
    next_frame(true);
}

Gif::~Gif() {
    if (gif) gd_close_gif(gif);
}

void Gif::next_frame(bool force) {
    if (!force && gif_timer.getElapsedTime().asMilliseconds() < gif->gce.delay * 10) return;
    gif_timer.restart();
    frame_n++;
    if (frame_n >= frames.size()) frame_n = 0;
    rect->setTexture(frames.at(frame_n).get());
}

void Gif::draw(sf::RenderWindow* fenster) {
    next_frame(false);
    fenster->draw(*rect);
}

void Gif::cache_frames() { // TODO perf extremely hot
    gd_rewind(gif);
    while (gd_get_frame(gif) == 1) {
        gd_render_frame(gif, frame.data());

        unsigned counter = 0;
        for (const auto& x : frame) {
            frame_rgba[counter] = x;
            counter++;
            if ((counter+1) % 4 == 0) { frame_rgba[counter] = 0xFF; counter++; }
        }

        sf::Image img;
        img.create(gif->width, gif->height, frame_rgba.data());
        std::unique_ptr<sf::Texture> temp_texture = std::make_unique<sf::Texture>();
        temp_texture->loadFromImage(img);
        frames.push_back(std::move(temp_texture));
    }
}
