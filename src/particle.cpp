#include <nada/particle.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace nada;

Particle::Particle() :
    Particle(
            {0.f, 0.f},
            20, 2,
            sf::Color(0xFFFFFFFF), 0.999f, 0.95f,
            4.f, 60.f, 0.5f, 0.001f,
            1.f,
            2.f, true)
{
    //
}

Particle::Particle(
        const sf::Vector2f& position,
        size_t aufloesung, size_t erzeugung,
        const sf::Color& farbe_start, float fade_farbe, float fade,
        float radius_start, float radius_ende, float radius_zufall, float radius_faktor,
        float geschwindigkeit,
        float jitter, bool respawn) :
        position(position),
        aufloesung(aufloesung),
        max_anzahl(erzeugung),
        farbe_start(farbe_start),
        fade_farbe(fade_farbe),
        radius_start(radius_start),
        radius_ende(radius_ende),
        radius_faktor(radius_faktor),
        radius_zufall(radius_zufall),
        geschwindigkeit(geschwindigkeit),
        fade(fade),
        jitter(jitter), respawn(respawn)
{
    particles.reserve(100);
    create_new();
}

void Particle::draw(sf::RenderWindow* window) {

    // Alte Particle entfernen
    particles.erase(
            std::remove_if(particles.begin(), particles.end(),
                    [this](const sf::CircleShape& k) {
                            // Tod durch Radius
                            if (radius_ende > radius_start && k.getRadius() > radius_ende) return true;
                            if (radius_ende < radius_start && k.getRadius() < radius_ende) return true;
                            return false;
                    }
                    ),
            particles.end()
    );

    // Neue hinzufügen
    if (respawn) create_new();

    // Alle zeichnen
    for (const auto& k : particles) window->draw(k); // TODO

    // Altern lassen
    for (sf::CircleShape& k : particles) {
        k.setPosition(
                0, // k.getPosition().x + nada::random::f(-jitter, jitter), TODO
                k.getPosition().y - geschwindigkeit
                );
        k.setFillColor(sf::Color(
                (float)k.getFillColor().r * fade_farbe,
                (float)k.getFillColor().g * fade_farbe,
                (float)k.getFillColor().b * fade_farbe,
                (float)k.getFillColor().a * fade
                ));
        k.setRadius(k.getRadius() + radius_faktor * ((radius_ende - radius_start)));
    }
}

void Particle::create_new() {
    const unsigned neue = 0; //nada::random::ui(0, max_anzahl ); TODO
    for (unsigned i = 0; i < neue; ++i) {
        sf::CircleShape k(
                //radius_start * nada::random::f(1.0f - radius_zufall, 1.0f + radius_zufall), TODO
                aufloesung
        );
        k.setPosition(position);
        k.setFillColor(farbe_start);
        k.setOutlineColor(farbe_start);
        particles.push_back(k);
    }
}

void Particle::set_position(const sf::Vector2f& position) {
    Particle::position = position;
}

void Particle::set_max_amount(size_t max_anzahl) {
    Particle::max_anzahl = max_anzahl;
}

void Particle::set_resolution(size_t aufloesung) {
    Particle::aufloesung = aufloesung;
}

void Particle::set_color_start(const sf::Color& farbe_start) {
    Particle::farbe_start = farbe_start;
}

void Particle::set_radius_start(float radius_start) {
    Particle::radius_start = radius_start;
}

void Particle::set_radius_end(float radius_ende) {
    Particle::radius_ende = radius_ende;
}

void Particle::set_start_velocity(float geschwindigkeit) {
    Particle::geschwindigkeit = geschwindigkeit;
}

void Particle::set_fade_color(float fade_farbe) {
    Particle::fade_farbe = fade_farbe;
}

void Particle::set_fade_speed(float fade_geschwindigkeit) {
    Particle::fade = fade_geschwindigkeit;
}

void Particle::set_jitter(float jitter) {
    Particle::jitter = jitter;
}

void Particle::set_respawn(bool respawn) {
    Particle::respawn = respawn;
}

Particle Particle::create_smoke() {
    return Particle(
            {0.f, 0.f},
            20, 2,
            sf::Color(0xFFFFFFFF), 0.999f, 0.999f,
            4.f, 60.f, 0.5f, 0.001f,
            1.f,
            2.f, true
    );
}

Particle Particle::create_fire() {
    return Particle(
            {0.f, 0.f},
            20, 2,
            sf::Color(0xFFAA22FF), 0.995f, 0.9999f,
            16.f, 1.f, 0.5f, 0.01f,
            3.f,
            1.f, true
    );
}
