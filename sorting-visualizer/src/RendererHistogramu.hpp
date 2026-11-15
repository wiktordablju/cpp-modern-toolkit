#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


namespace Layout {
    constexpr unsigned int WIN_W = 1680;
    constexpr unsigned int WIN_H = 1050;

    constexpr float CTRL_H = 72.f;

    constexpr float BOT_H  = WIN_H * 0.45f;

    constexpr float HIST_H = WIN_H - CTRL_H - BOT_H;

    constexpr float CTRL_Y = HIST_H;
    constexpr float BOT_Y  = CTRL_Y + CTRL_H;

    constexpr float DIVIDER_X = WIN_W / 2.f;

    constexpr float HIST_PAD_X   = 60.f;
    constexpr float HIST_PAD_TOP = 20.f;
    constexpr float HIST_PAD_BOT = 35.f;
    constexpr float BAR_GAP      = 10.f;
    constexpr int   BAR_COUNT    = 10;

    constexpr float BAR_W =
        (WIN_W - 2 * HIST_PAD_X - (BAR_COUNT - 1) * BAR_GAP)
        / static_cast<float>(BAR_COUNT);

    constexpr float BAR_MAX_H =
        HIST_H - HIST_PAD_TOP - HIST_PAD_BOT;

    constexpr int DATA_MAX = 50;
}

class RendererHistogramu {
private:
    const sf::Font* czcionka = nullptr;

    sf::Color kolorNormalny    { 70,  130, 180 };
    sf::Color kolorIndeksA     { 220,  50,  50 };
    sf::Color kolorIndeksB     {  50, 180,  80 };
    sf::Color kolorTlo         { 250, 250, 252 };

    float barX(int i) const;
    float barH(int wartosc) const;

public:
    void setCzcionka(const sf::Font& font);

    void RysujSlupki(sf::RenderWindow& window,
                     const std::vector<int>& dane,
                     int indeksA = -1,
                     int indeksB = -1);

    void RysujPodswietlenie(sf::RenderWindow& window, int indeksA, int indeksB);
    void RysujWartosci(sf::RenderWindow& window, const std::vector<int>& dane);
};
