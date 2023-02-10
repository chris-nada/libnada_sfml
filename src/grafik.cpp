#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <webp/decode.h>
#include <functional>
#include <nada/grafik.hpp>

using namespace nada;

Graphic::Graphic() :is_shared(false), is_flipped(false) { }

Graphic::Graphic(const std::string& textur_pfad, bool is_shared) :
        is_shared(is_shared),
        is_flipped(false),
        textur_pfad(textur_pfad)
{
    // Textur noch nicht vorhanden
    textur = std::make_unique<sf::Texture>();

    // webp laden
    if (textur_pfad.find(".webp") != std::string::npos) {
        if (std::ifstream in(textur_pfad); in.good()) {
            const std::string data = std::invoke([&](){ std::ostringstream oss; oss << in.rdbuf(); return oss.str(); });
            int width = 0, height = 0;
            webp_data.reset(WebPDecodeRGBA((uint8_t*)data.data(), data.size(), &width, &height));
            if (webp_data == nullptr) {
                std::cerr << "Graphic() webp texture " << textur_pfad << " could not be loaded.\n";
                textur.reset(nullptr);
            }
            else {
                textur->create(width, height);
                textur->update(webp_data.get(), width, height, 0, 0);
            }
        }
    }
    // andere formate
    else if (textur->loadFromFile(textur_pfad)) std::cout << "\t\tGraphic() loaded from " << textur_pfad << '\n';
    else {
        std::cerr << "Graphic() texture could not be loaded from " << textur_pfad << "\n";
        textur.reset(nullptr);
    }

    // Textur setzen
    sprite = std::make_unique<sf::Sprite>();
    if (textur) sprite->setTexture(*textur);
}

Graphic::operator bool() const { return textur!=nullptr; }

bool Graphic::operator==(const Graphic& rhs) const { return textur==rhs.textur; }

bool Graphic::operator!=(const Graphic& rhs) const { return !(rhs==*this); }

void Graphic::set_flip(bool flip) {
    if (flip == is_flipped) return;
    const auto& r = sprite->getTextureRect();
    if (flip) {
        sprite->setTextureRect(sf::IntRect(std::abs(r.width), 0, -std::abs(r.width), r.height));
    }
    else {
        sprite->setTextureRect(sf::IntRect(0, 0, std::abs(r.width), r.height));
    }
    is_flipped = flip;
}

void Graphic::set_size(const sf::Vector2f& size) {
    sprite->setScale(size.x / textur->getSize().x, size.y / textur->getSize().y);
}

sf::Vector2f Graphic::size_f() const {
    return sf::Vector2f(size().x, size().y);
}

bool Graphic::is_inside(float x, float y) const {
    return sprite->getGlobalBounds().contains(x, y);
}

const std::string& Graphic::get_info() const {
    return info;
}

void Graphic::draw(sf::RenderWindow* fenster) {
    fenster->draw(*sprite);
}

void Graphic::set_opacity(float faktor) {
    auto color = sprite->getColor();
    color.a = 0xFF * faktor;
    sprite->setColor(color);
}

void Graphic::delete_file() {
    try {
        std::filesystem::path path(this->get_pfad());
        std::filesystem::remove(path);
    }
    catch (const std::exception& e) {}
}

void Graphic::set_color(const sf::Color& color) { sprite->setColor(color); }

void Graphic::set_size(float scale) { sprite->setScale(scale, scale); }

void Graphic::set_x(float x) { sprite->setPosition(x, sprite->getPosition().y); }

void Graphic::set_y(float y) { sprite->setPosition(sprite->getPosition().x, y); }

void Graphic::set_pos(const sf::Vector2f& pos) { sprite->setPosition(pos); }

float Graphic::size_x() const { return textur->getSize().x * sprite->getScale().x; }

float Graphic::size_y() const { return textur->getSize().y * sprite->getScale().y; }

sf::Vector2u Graphic::size() const { return textur->getSize(); }

bool Graphic::good() const { return textur!=nullptr; }

sf::Texture* Graphic::data() const { return textur.get(); }

const sf::Vector2f& Graphic::pos() const { return sprite->getPosition(); }

float Graphic::x() const { return sprite->getPosition().x; }

float Graphic::y() const { return sprite->getPosition().y; }

void Graphic::set_info(const std::string& info) { this->info = info; }
