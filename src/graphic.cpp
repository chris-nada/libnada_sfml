#include <nada/graphic.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <memory>
#include <fstream>
#include <filesystem>
#include <functional>
#include <webp/decode.h>

using namespace nada;

Graphic::Graphic() :is_shared(false), is_flipped(false) { }

Graphic::Graphic(const std::string& textur_pfad, bool is_shared) :
        is_shared(is_shared),
        is_flipped(false),
        textur_pfad(textur_pfad)
{
    // Is already cached?
    static std::unordered_map<std::string, sf::Texture*> cache;

    // Textur noch nicht vorhanden?
    textur = nullptr;
    if (is_shared && cache.count(textur_pfad)) textur = cache[textur_pfad];

    if (textur ==nullptr) {
        textur = new sf::Texture;

        // webp laden
        if (textur_pfad.find(".webp")!=std::string::npos) {
            if (std::ifstream in(textur_pfad); in.good()) {
                const std::string data = std::invoke([&]() {
                    std::ostringstream oss;
                    oss << in.rdbuf();
                    return oss.str();
                });
                int width = 0, height = 0;
                webp_data.reset(WebPDecodeRGBA((uint8_t*) data.data(), data.size(), &width, &height));
                if (webp_data==nullptr) {
                    std::cerr << "Graphic() webp texture " << textur_pfad << " could not be loaded.\n";
                    delete textur;
                    textur = nullptr;
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
            delete textur;
            textur = nullptr;
        }
    }

    // Textur setzen
    rect = std::make_unique<sf::RectangleShape>();
    if (textur) {
        rect->setTexture(textur, true);
        if (is_shared) cache[textur_pfad] = textur;
    }
}

Graphic::~Graphic() {
    if (!is_shared) delete textur;
}

bool Graphic::good() const { return textur != nullptr; }
Graphic::operator bool() const { return textur != nullptr; }

bool Graphic::operator==(const Graphic& rhs) const { return textur==rhs.textur; }

bool Graphic::operator!=(const Graphic& rhs) const { return !(rhs==*this); }

void Graphic::set_flip(bool flip) {
    if (flip == is_flipped) return;
    const auto& r = rect->getTextureRect();
    if (flip) {
        rect->setTextureRect(sf::IntRect(std::abs(r.width), 0, -std::abs(r.width), r.height));
    }
    else {
        rect->setTextureRect(sf::IntRect(0, 0, std::abs(r.width), r.height));
    }
    is_flipped = flip;
}

void Graphic::set_size(const sf::Vector2f& size) {
    rect->setScale(size.x / textur->getSize().x, size.y / textur->getSize().y);
}

sf::Vector2f Graphic::size_f() const {
    return sf::Vector2f(size().x, size().y);
}

bool Graphic::is_inside(float x, float y) const {
    return rect->getGlobalBounds().contains(x, y);
}

const std::string& Graphic::get_info() const {
    return info;
}

void Graphic::draw(sf::RenderWindow* fenster) {
    fenster->draw(*rect);
}

void Graphic::set_opacity(float faktor) {
    auto color = rect->getFillColor();
    color.a = 0xFF * faktor;
    rect->setFillColor(color);
}

void Graphic::delete_file() {
    try {
        std::filesystem::path path(this->get_pfad());
        std::filesystem::remove(path);
    }
    catch (const std::exception& e) {}
}

void Graphic::set_color(const sf::Color& color) { rect->setFillColor(color); }

void Graphic::set_size(float scale) { rect->setScale(scale, scale); }

void Graphic::set_x(float x) { rect->setPosition(x, rect->getPosition().y); }

void Graphic::set_y(float y) { rect->setPosition(rect->getPosition().x, y); }

void Graphic::set_pos(const sf::Vector2f& pos) { rect->setPosition(pos); }

float Graphic::size_x() const { return textur->getSize().x * rect->getScale().x; }

float Graphic::size_y() const { return textur->getSize().y * rect->getScale().y; }

sf::Vector2u Graphic::size() const { return textur->getSize(); }

sf::Texture* Graphic::data() const { return textur; }

const sf::Vector2f& Graphic::pos() const { return rect->getPosition(); }

float Graphic::x() const { return rect->getPosition().x; }

float Graphic::y() const { return rect->getPosition().y; }

void Graphic::set_info(const std::string& info) { this->info = info; }
