#include <nada/multigraphic.hpp>
#include <nada/graphic.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

using namespace nada;

nada::Multigraphic::Multigraphic(const std::vector<std::string>& grafik_pfade, int x, int y) :
    size_x(0), size_y(0), alle_grafiken_valide(false)
{
    alle_grafiken_valide = !grafik_pfade.empty();
    for (const auto& pfad : grafik_pfade) {
        auto t = grafiken.emplace_back(new Graphic(pfad));
        if (t->good()) {
            if (size_x > 0 && size_y > 0 && (size_x != t->size().x || size_y != t->size().y)) {
                std::cerr << "Warning: Wrong GFX size for: " << pfad << ": " << size_x << 'x' << size_y
                           << " Expected: " << t->size().x << 'x' << t->size().y << " Graphic glitches probable.\n";
            }
            t->set_pos({static_cast<float>(x), static_cast<float>(y)});
            size_x = t->size().x;
            size_y = t->size().y;
        }
        else alle_grafiken_valide = false;
    }
}

Multigraphic::~Multigraphic() {
    for (auto g : grafiken) delete g;
}

void Multigraphic::draw(sf::RenderWindow* fenster, unsigned frame) {
    if (!good()) return;
    grafiken[frame]->draw(fenster);
}

bool Multigraphic::is_inside(float x, float y) const {
    if (!good()) return false;
    const auto& g = grafiken[0];
    return g->is_inside(x, y);
}

bool Multigraphic::good() const {
    return !grafiken.empty() && alle_grafiken_valide;
}
