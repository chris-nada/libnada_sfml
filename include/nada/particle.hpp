#pragma once

#include <SFML/Graphics/CircleShape.hpp>

namespace sf { class RenderWindow; }

namespace nada {

/// Einfaches, auf Kreisen basierendes Partikelsystem. // TODO translate doc
class Particle final {

public:

    /// Liefert einen vorgefertigten Rauch-Emitter.
    static Particle create_smoke();

    /// Liefert einen vorgefertigten Feuer-Emitter.
    static Particle create_fire();

    /// Erzeugt einen Partikelemitter. Sollte anschließend konfiguriert werden.
    Particle();

    /**
     * @brief Erzeugt einen Partikelemitter.
     *
     * @param position          Bildschirmposition.
     * @param aufloesung        Anzahl Kanten pro Kreis. Weniger => bessere Performanz.
     * @param erzeugung         Wieviele pro draw() maximal erzeugt werden dürfen.
     * @param farbe_start       Anfängliche Farbe.
     * @param fade_farbe        Faktor, mit dem die Farbe abnimmt. 1.0 = bleibt.
     * @param radius_start      Anfänglicher Radius.
     * @param radius_ende       Radius, dessen Über/Unterschreitung zur Auslöschung führt.
     * @param radius_zufall     Faktor, um den der Anfangsradius variieren darf. Z.B. 0.5 = 50%.
     * @param radius_faktor     Faktor, mit dem der Radius abnimmt. 0.1 = sehr schnell, 0.0001 langsam.
     * @param geschwindigkeit   Pixel pro draw(), die sich die Partikel bewegen.
     * @param fade              Faktor, mit dem der Alphawert der Partikel abnimmt (z.B. 0.99 pro draw()).
     * @param jitter            Pixel pro draw(), die sich ein Partikel zufällig horizontal bewegt.
     * @param respawn           True
     */
    Particle(const sf::Vector2f& position,
             size_t aufloesung, size_t erzeugung,
             const sf::Color& farbe_start, float fade_farbe,
             float radius_start, float radius_ende,
             float radius_zufall = 0.5f, float radius_faktor = 0.001f,
             float geschwindigkeit = 1.5f, float fade = 0.999f,
             float jitter = 2.f, bool respawn = true);

    /// Draws this to given window.
    void draw(sf::RenderWindow* window);

    void set_position(const sf::Vector2f& position);

    void set_resolution(size_t resolution);

    void set_max_amount(size_t max_amount);

    void set_color_start(const sf::Color& start_color);

    void set_radius_start(float radius_start);

    void set_radius_end(float radius_end);

    void set_start_velocity(float start_velocity);

    void set_fade_color(float fade_color);

    void set_fade_speed(float fade_speed);

    void set_jitter(float jitter);

    void set_respawn(bool respawn);

private:

    void create_new();

    /// Partikelspeicher.
    std::vector<sf::CircleShape> particles;

    /// Startposition der Partikel.
    sf::Vector2f position;

    /// Anzahl Kanten. Mehr Kanten => weniger eckig.
    std::size_t aufloesung;

    /// Anzahl zu Beginn auszusendender Partikel.
    std::size_t max_anzahl;

    /// Farbe, die neue Partikel bekommen.
    sf::Color farbe_start;

    /// Farbe zu der ausgefaded wird.
    float fade_farbe;

    /// Radius zu Beginn der Aussendung.
    float radius_start;

    /// Radius bei Ende der Aussendung.
    float radius_ende;

    /// Wachstumsfaktor Radius. Muss zwischen 0 und 1 liegen.
    float radius_faktor;

    /// Zufällige Startabweichung beim Radius.
    float radius_zufall;

    /// Anfängliche Geschwindigkeit in Pixel pro Frame.
    float geschwindigkeit;

    /// Faktor wie schnell der Partikel schwindet.
    float fade;

    /// Zufällige horizontale Bewegung je Frame.
    float jitter;

    /// Sollen statig neue Partikel ausgesendet werden?
    bool respawn;

};

} // namespace nada
