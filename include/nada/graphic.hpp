#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf { class Sprite; class Texture; class RenderWindow; }

namespace nada {

/**
 * Helper class that adds GIF and webp support to SFML graphics.
 * Basically a wrapper around sf::Texture.
 */
class Graphic {

public:

    /**
     * Loads a graphic from given file (`jpg`, `png` ...). Formats: everything SFML supports + GIF + webp.
     * @param texture_path absolute or relative path to image file.
     * @param is_shared `true` if this graphic should use a "cache". Set to `true`, if you use the same graphic over and
     *                  over to safe loading times (from filesystem-IO).
     */
    explicit Graphic(const std::string& texture_path, bool is_shared = false);

    /// Draw this to given window.
    virtual void draw(sf::RenderWindow* window);

    /// Getter: X-Koordinate.
    [[nodiscard]] float x() const;

    /// Getter: Y-Koordinate.
    [[nodiscard]] float y() const;

    /// Getter: Position as SFML vector.
    [[nodiscard]] const sf::Vector2f& pos() const;

    /// Is given point inside this?
    [[nodiscard]] bool is_inside(float x, float y) const;

    /// Getter for a pointer to used raw SFML texture.
    [[nodiscard]] sf::Texture* data() const;

    /// Graphic ready to be drawn?
    [[nodiscard]] bool good() const;

    /// Getter for texture dimensions.
    [[nodiscard]] sf::Vector2u size() const;

    /// Getter for texture width.
    [[nodiscard]] float size_x() const;

    /// Getter for texture height.
    [[nodiscard]] float size_y() const;

    /// Getter for this graphic's dimensions, converted to float.
    [[nodiscard]] sf::Vector2f size_f() const;

    /// Getter for custom data, that you may have attached to this as a std::string.
    [[nodiscard]] const std::string& get_info() const;

    /// Getter for filesystem path, from which this graphic was loaded.
    [[nodiscard]] const std::string& get_pfad() const { return textur_pfad; }

    /// Manipulates (multiplies) this by given color.
    void set_color(const sf::Color& color);

    /// Set opacity. Valid range from 0.0 (invisible) to 1.0 (totally opaque).
    void set_opacity(float faktor);

    /// Skaliert die Graphic auf gegebene Größe in Pixel.
    void set_size(const sf::Vector2f& size);

    /// Multiplies size by given scale. 2.0 would mean doulbe size, 0.5 half size and so on.
    void set_size(float scale);

    /// Setter: X-Position.
    void set_x(float x);

    /// Setter: Y-Position.
    void set_y(float y);

    /// Setter: Position as (SFML)-Vector.
    void set_pos(const sf::Vector2f& pos);

    /// Setter: Flip this graphic horizontally? Off by default. @param flip true=flip on, false=flip off.
    void set_flip(bool flip);

    /// Setter for custom data, that you may attach to this as a std::string. Does nothing else. For your eyes only.
    void set_info(const std::string& info);

    /// Remove associated file. Graphic stays valid (in memory) after this operation. Does nothing if IO-error.
    void delete_file();

    /// Kann verwendet werden, um zu prüfen, ob eine Graphic geladen ist.
    explicit operator bool() const;

    /// Checks, if this graphic uses the same allocated texture image as `rhs`.
    bool operator==(const Graphic& rhs) const;

    /// Checks, if this graphic does not use the same allocated texture image as `rhs`.
    bool operator!=(const Graphic& rhs) const;

protected:

    /**
     *  Konstruktor.
     *  @note `is_shared` = true means, dass die Graphic nicht gelöscht wird nach ableben der Instanz.
     */
    Graphic();

    bool is_shared;

    bool is_flipped;

    std::string textur_pfad;

    std::unique_ptr<sf::Texture> textur;

    std::unique_ptr<sf::Sprite> sprite;

    std::unique_ptr<uint8_t> webp_data;

    std::string info;

};

} // namespace nada
