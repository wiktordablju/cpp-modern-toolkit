#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>
#include "InformacjeAlgorytmu.hpp"
#include "StanProgramu.hpp"

enum class AkcjaUI {
    Brak,
    PoprzedniKrok,
    NastepnyKrok,
    SortujAutomatycznie,
    StopSortowanie,
    ZapiszHistorie,
    Reset,
    PokazHistorie,
    NastepnyAlgorytm,
    PoprzedniAlgorytm
};

struct Button {
    sf::RectangleShape tlo;
    std::string etykieta;
    const sf::Font* etykietaFont = nullptr;
    unsigned int etykietaRozmiar = 13;
    bool wlaczony = true;

    void setGeometry(float x, float y, float w, float h);
    void setLabel(const std::string& tekst, const sf::Font& font, unsigned int rozmiar = 13);
    bool zawiera(sf::Vector2f pos) const;
    void rysuj(sf::RenderWindow& window) const;
};

class InterfejsUzytkownika {
private:
    const sf::Font* czcionka = nullptr;

    Button btnPoprzedni;
    Button btnNastepny;
    Button btnAutoSort;
    Button btnStop;
    Button btnZapisz;
    Button btnReset;
    Button btnHistoria;
    Button btnPrevAlgo;
    Button btnNextAlgo;

    sf::RectangleShape suwakTlo;
    sf::RectangleShape suwakKursor;

    float predkosc = 1.f;
    bool suwakPrzeciagany = false;
    int historiaScroll = 0;

    std::optional<sf::Text> labelAlgorytm;

    void rysujPanelKodu(sf::RenderWindow&, const std::string&) const;
    void rysujPanelZlozonosci(sf::RenderWindow&, const InformacjeAlgorytmu&) const;
    void rysujPanelKrokow(sf::RenderWindow&, const std::vector<std::string>&, int);

    void aktualizujSuwak(float mouseX);
    void ustawPredkosc(float wartosc);
    float predkoscDoPixel() const;

public:
    void setCzcionka(const sf::Font& font);
    void inicjalizuj();
    void przewinHistorie(int delta);
    void resetHistorii();

    AkcjaUI ObsluzWejscie(const sf::Event&, sf::RenderWindow&, StanProgramu);

    void RysujInterfejs(sf::RenderWindow&,
                        const InformacjeAlgorytmu&,
                        StanProgramu,
                        const std::string&,
                        const std::vector<std::string>& = {},
                        int = 0);

    float getPredkosc() const { return predkosc; }
};