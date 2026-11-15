#include "RendererHistogramu.hpp"
#include <algorithm>
#include <string>

namespace {

sf::Text makeText(const sf::Font& font,
                  const std::string& tekst,
                  unsigned int rozmiar = 13,
                  sf::Color kolor = sf::Color::White) {
    sf::Text text{font, tekst, rozmiar};

    text.setFillColor(kolor);
    return text;
}

} // namespace


float RendererHistogramu::barX(int i) const {
    return Layout::HIST_PAD_X + i * (Layout::BAR_W + Layout::BAR_GAP);
}

float RendererHistogramu::barH(int wartosc) const {
    float h = (static_cast<float>(wartosc) / Layout::DATA_MAX) * Layout::BAR_MAX_H;
    return std::max(5.f, h);
}

void RendererHistogramu::setCzcionka(const sf::Font& font) {
    czcionka = &font;
}


void RendererHistogramu::RysujSlupki(sf::RenderWindow& window,
                                      const std::vector<int>& dane,
                                      int indeksA,
                                      int indeksB) {
    sf::RectangleShape tlo({ static_cast<float>(Layout::WIN_W), Layout::HIST_H });
    tlo.setPosition(sf::Vector2f{0.f, 0.f});
    tlo.setFillColor(kolorTlo);
    window.draw(tlo);

    const int n = static_cast<int>(dane.size());
    for (int i = 0; i < n; ++i) {
        float h  = barH(dane[i]);
        float x  = barX(i);
        float y  = Layout::HIST_H - Layout::HIST_PAD_BOT - h;

        sf::RectangleShape slupek({ Layout::BAR_W, h });
        slupek.setPosition(sf::Vector2f{x, y});

        if (i == indeksA)       slupek.setFillColor(kolorIndeksA);
        else if (i == indeksB)  slupek.setFillColor(kolorIndeksB);
        else                    slupek.setFillColor(kolorNormalny);

        window.draw(slupek);
    }

    RysujWartosci(window, dane);
}

void RendererHistogramu::RysujPodswietlenie(sf::RenderWindow& window,
                                             int indeksA,
                                             int indeksB) {

    auto rysujOverlay = [&](int idx, sf::Color kolor) {
        if (idx < 0) return;
        kolor.a = 60;
        sf::RectangleShape overlay({ Layout::BAR_W, Layout::HIST_H });
        overlay.setPosition(sf::Vector2f{barX(idx), 0.f});
        overlay.setFillColor(kolor);
        window.draw(overlay);
    };

    rysujOverlay(indeksA, kolorIndeksA);
    rysujOverlay(indeksB, kolorIndeksB);
}

void RendererHistogramu::RysujWartosci(sf::RenderWindow& window, const std::vector<int>& dane) {
    if (!czcionka) return;

    const int n = static_cast<int>(dane.size());
    for (int i = 0; i < n; ++i) {
        sf::Text tekst = makeText(*czcionka, std::to_string(dane[i]), 13, sf::Color(40, 40, 40));

        sf::FloatRect bounds = tekst.getLocalBounds();
        float textWidth =
            bounds.size.x;

        float cx = barX(i) + (Layout::BAR_W - textWidth) / 2.f;
        float cy = Layout::HIST_H - Layout::HIST_PAD_BOT + 6.f;
        tekst.setPosition(sf::Vector2f{cx, cy});
        window.draw(tekst);
    }
}
