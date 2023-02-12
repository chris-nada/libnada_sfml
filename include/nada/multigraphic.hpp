#pragma once

#include <vector>
#include <string>

namespace sf { class RenderWindow; }

namespace nada {

    class Graphic;

/**
 * TODO translate
 */
class Multigraphic final {

public:

    /**
     * Erzeugt eine Multi-Frame-Grafik aus gegebenen Bildern (via Pfade) bei Position x_pos, y_pos.
     * @note Grafik ist so groß wie die Originale. Diese sollten gleich groß sein.
     */
    Multigraphic(const std::vector<std::string>& grafik_pfade, int x_pos, int y_pos);

    ~Multigraphic();

    /// Zeichnet Textur Nummer `frame` (beginnened mit 0) auf das gegebene Fenster.
    void draw(sf::RenderWindow* fenster, unsigned frame);

    /// Wurden Texturen erfolgreich geladen?
    [[nodiscard]] bool good() const;

    /// Größe x.
    [[nodiscard]] unsigned get_size_x() const { return size_x; }

    /// Größe y.
    [[nodiscard]] unsigned get_size_y() const { return size_y; }

    /// Befindet sich gegebener Punkt innerhalb der Grafik?
    [[nodiscard]] bool is_inside(float x, float y) const;

private:

    std::vector<Graphic*> grafiken;
    unsigned size_x;
    unsigned size_y;
    bool alle_grafiken_valide;

};
} // namespace
