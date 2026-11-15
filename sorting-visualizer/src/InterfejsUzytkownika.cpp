#include "InterfejsUzytkownika.hpp"
#include "RendererHistogramu.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <sstream>


static const sf::Color CLR_CTRL_BG   { 215, 215, 220 };
static const sf::Color CLR_PANEL_BG  { 252, 252, 255 };
static const sf::Color CLR_BTN       { 235, 235, 240 };
static const sf::Color CLR_BTN_HOV   { 200, 205, 215 };
static const sf::Color CLR_BTN_DIS   { 210, 210, 212 };
static const sf::Color CLR_BTN_BDR   { 160, 160, 170 };
static const sf::Color CLR_TEXT      {  30,  30,  35 };
static const sf::Color CLR_TEXT_DIS  { 160, 160, 165 };
static const sf::Color CLR_HDR       {  50,  50,  60 };
static const sf::Color CLR_DIVIDER   { 180, 180, 185 };
static const sf::Color CLR_CODE_BG   {  28,  28,  35 };
static const sf::Color CLR_CODE_TXT  { 200, 220, 200 };
static const sf::Color CLR_SLIDER_TL { 175, 175, 180 };
static const sf::Color CLR_SLIDER_KR {  80, 110, 180 };
static const float CTRL_Y = Layout::CTRL_Y;
static const float CTRL_H = Layout::CTRL_H;
static const float SLIDER_X = 650.f;
static const float SLIDER_W = 150.f;
static const float SLIDER_H = 6.f;
static const float SLIDER_Y = CTRL_Y + (CTRL_H - SLIDER_H) / 2.f;
static const float SLIDER_KMIN = 0.25f;
static const float SLIDER_KMAX = 4.0f;

namespace {

sf::Text makeText(const sf::Font& font,
                  const std::string& tekst = {},
                  unsigned int rozmiar = 13,
                  sf::Color kolor = CLR_TEXT) {
    sf::Text text{font, tekst, rozmiar};
    text.setFillColor(kolor);
    return text;
}

float rectLeft(const sf::FloatRect& rect) {
    return rect.position.x;

}

float rectTop(const sf::FloatRect& rect) {
    return rect.position.y;
}

float rectWidth(const sf::FloatRect& rect) {
    return rect.size.x;
}

float rectHeight(const sf::FloatRect& rect) {
    return rect.size.y;
}

void setBoldStyle(sf::Text& text) {
    text.setStyle(sf::Text::Style::Bold);
}

} // namespace

void Button::setGeometry(float x, float y, float w, float h) {
    tlo.setSize({ w, h });
    tlo.setPosition(sf::Vector2f{x, y});
    tlo.setFillColor(CLR_BTN);
    tlo.setOutlineThickness(1.f);
    tlo.setOutlineColor(CLR_BTN_BDR);
}

void Button::setLabel(const std::string& tekst, const sf::Font& font, unsigned int rozmiar) {
    etykieta = tekst;
    etykietaFont = &font;
    etykietaRozmiar = rozmiar;
}

bool Button::zawiera(sf::Vector2f pos) const {
    return tlo.getGlobalBounds().contains(pos);
}

void Button::rysuj(sf::RenderWindow& window) const {
    sf::RectangleShape kopia = tlo;
    if (!wlaczony) {
        kopia.setFillColor(CLR_BTN_DIS);
    }
    window.draw(kopia);

    if (!etykietaFont) return;
    sf::Text t = makeText(*etykietaFont, etykieta, etykietaRozmiar,
                          wlaczony ? CLR_TEXT : CLR_TEXT_DIS);
    sf::FloatRect tb = t.getLocalBounds();
    sf::FloatRect sb = tlo.getGlobalBounds();
    t.setPosition(sf::Vector2f{
        rectLeft(sb) + (rectWidth(sb)  - rectWidth(tb)  - rectLeft(tb)) / 2.f,
        rectTop(sb)  + (rectHeight(sb) - rectHeight(tb) - rectTop(tb)) / 2.f});
    window.draw(t);
}

void InterfejsUzytkownika::setCzcionka(const sf::Font& font) {
    czcionka = &font;
}

void InterfejsUzytkownika::inicjalizuj() {
    if (!czcionka) return;

    const float BTN_H = 34.f;
    const float BTN_Y = CTRL_Y + (CTRL_H - BTN_H) / 2.f;
    float x = 10.f;

    auto makeBtn = [&](Button& b, const std::string& label, float w) {
        b.setGeometry(x, BTN_Y, w, BTN_H);
        b.setLabel(label, *czcionka, 12);
        x += w + 6.f;
    };

    makeBtn(btnPoprzedni, "< Poprzedni",   110.f);
    makeBtn(btnNastepny,  "Nastepny >",    100.f);
    makeBtn(btnAutoSort,  "Auto-Sort",      90.f);
    makeBtn(btnStop,      "Stop",           60.f);
    makeBtn(btnReset,     "Reset",          65.f);
    makeBtn(btnHistoria,  "Historia",       75.f);
    makeBtn(btnZapisz,    "Zapisz", 60.f);

    suwakTlo.setSize({ SLIDER_W, SLIDER_H });
    suwakTlo.setPosition(sf::Vector2f{SLIDER_X, SLIDER_Y});
    suwakTlo.setFillColor(CLR_SLIDER_TL);

    suwakKursor.setSize({ 10.f, 18.f });
    suwakKursor.setFillColor(CLR_SLIDER_KR);
    float kx = predkoscDoPixel();
    suwakKursor.setPosition(sf::Vector2f{
        kx - 5.f,
        SLIDER_Y - 6.f
    });

    const float ALGO_BTN_W = 40.f;

    const float algoX = SLIDER_X + SLIDER_W + 70.f;

    btnPrevAlgo.setGeometry(algoX, CTRL_Y + 18.f, ALGO_BTN_W, 36.f);
    btnNextAlgo.setGeometry(algoX + 360.f, CTRL_Y + 18.f, ALGO_BTN_W, 36.f);

    btnNextAlgo.setLabel(">", *czcionka, 14);
    btnPrevAlgo.setLabel("<", *czcionka, 14);
    
    if (!labelAlgorytm) {
        labelAlgorytm.emplace(*czcionka, "", 13);

    } else {
        labelAlgorytm->setFont(*czcionka);
        labelAlgorytm->setCharacterSize(13);
    }
    labelAlgorytm->setFillColor(CLR_TEXT);
}

float InterfejsUzytkownika::predkoscDoPixel() const {
    float t = (predkosc - SLIDER_KMIN) / (SLIDER_KMAX - SLIDER_KMIN);
    return SLIDER_X + t * SLIDER_W;
}

void InterfejsUzytkownika::aktualizujSuwak(float mouseX) {
    float x = std::clamp(mouseX, SLIDER_X, SLIDER_X + SLIDER_W);
    float t = (x - SLIDER_X) / SLIDER_W;

    ustawPredkosc(SLIDER_KMIN + t * (SLIDER_KMAX - SLIDER_KMIN));

    suwakKursor.setPosition(sf::Vector2f{
        x - 5.f,
        SLIDER_Y - 6.f
    });
}

void InterfejsUzytkownika::ustawPredkosc(float wartosc) {
    predkosc = std::clamp(wartosc, SLIDER_KMIN, SLIDER_KMAX);
}

void InterfejsUzytkownika::przewinHistorie(int delta) {
    historiaScroll = std::max(0, historiaScroll + delta);
}

void InterfejsUzytkownika::resetHistorii() {
    historiaScroll = 0;
}

AkcjaUI InterfejsUzytkownika::ObsluzWejscie(const sf::Event& event, sf::RenderWindow& window, StanProgramu stan) {
    const float popupX = 120.f;
    const float popupY = 80.f;
    const float popupW = 1040.f;
    const float popupH = 560.f;
    if (stan == StanProgramu::Historia) {
        if (event.is<sf::Event::MouseWheelScrolled>()) {
            const auto* wheel = event.getIf<sf::Event::MouseWheelScrolled>();
            if (wheel) przewinHistorie(static_cast<int>(-wheel->delta * 3.f));
            return AkcjaUI::Brak;
        }
        if (event.is<sf::Event::MouseButtonPressed>()) {
            const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>();
            if (!mouse) return AkcjaUI::Brak;
            sf::Vector2f klik = window.mapPixelToCoords({ mouse->position.x, mouse->position.y });
            if (klik.x >= popupX + popupW - 106.f && klik.x <= popupX + popupW - 20.f &&
                klik.y >= popupY + 12.f && klik.y <= popupY + 40.f) {
                return AkcjaUI::PokazHistorie;
            }
            if (klik.x < popupX || klik.x > popupX + popupW || klik.y < popupY || klik.y > popupY + popupH) {
                return AkcjaUI::PokazHistorie;
            }
        }
        return AkcjaUI::Brak;
    }

    sf::Vector2i pos{ 0, 0 };
    bool maKlik = false;
    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>();
        if (!mouse) return AkcjaUI::Brak;
        pos = { mouse->position.x, mouse->position.y };
        maKlik = true;
    }
    if (event.is<sf::Event::MouseButtonReleased>()) {
        suwakPrzeciagany = false;
        return AkcjaUI::Brak;
    }
    if (event.is<sf::Event::MouseMoved>()) {
        if (suwakPrzeciagany) {
            const auto* move = event.getIf<sf::Event::MouseMoved>();
            if (move) aktualizujSuwak(window.mapPixelToCoords({ move->position.x, move->position.y }).x);
        }
        return AkcjaUI::Brak;
    }
    if (!maKlik) return AkcjaUI::Brak;

    sf::Vector2f klik = window.mapPixelToCoords(pos);
    sf::FloatRect suwakArea{ {SLIDER_X - 5.f, CTRL_Y + 10.f}, {SLIDER_W + 10.f, CTRL_H - 20.f} };
    if (suwakArea.contains(klik)) {
        suwakPrzeciagany = true;
        aktualizujSuwak(klik.x);
        return AkcjaUI::Brak;
    }

    if (btnPoprzedni.zawiera(klik) && btnPoprzedni.wlaczony) return AkcjaUI::PoprzedniKrok;
    if (btnNastepny.zawiera(klik)  && btnNastepny.wlaczony)  return AkcjaUI::NastepnyKrok;
    if (btnAutoSort.zawiera(klik)  && btnAutoSort.wlaczony)  return AkcjaUI::SortujAutomatycznie;
    if (btnStop.zawiera(klik)      && btnStop.wlaczony)      return AkcjaUI::StopSortowanie;
    if (btnZapisz.zawiera(klik)    && btnZapisz.wlaczony)    return AkcjaUI::ZapiszHistorie;
    if (btnReset.zawiera(klik)     && btnReset.wlaczony)     return AkcjaUI::Reset;
    if (btnHistoria.zawiera(klik)  && btnHistoria.wlaczony)  return AkcjaUI::PokazHistorie;
    if (btnPrevAlgo.zawiera(klik))                           return AkcjaUI::PoprzedniAlgorytm;
    if (btnNextAlgo.zawiera(klik))                           return AkcjaUI::NastepnyAlgorytm;

    return AkcjaUI::Brak;
}

void InterfejsUzytkownika::rysujPanelKodu(sf::RenderWindow& window, const std::string& kod) const {
    if (!czcionka) return;

    sf::RectangleShape tlo({ Layout::DIVIDER_X, Layout::BOT_H });
    tlo.setPosition(sf::Vector2f{0.f, Layout::BOT_Y});
    tlo.setFillColor(CLR_CODE_BG);
    window.draw(tlo);

    sf::Text hdr = makeText(*czcionka, "KOD ALGORYTMU", 14, sf::Color(180, 200, 255));
    setBoldStyle(hdr);
    hdr.setPosition(sf::Vector2f{14.f, Layout::BOT_Y + 10.f});
    window.draw(hdr);

    sf::RectangleShape sep({ Layout::DIVIDER_X - 28.f, 1.f });
    sep.setPosition(sf::Vector2f{14.f, Layout::BOT_Y + 32.f});
    sep.setFillColor(sf::Color(80, 90, 110));
    window.draw(sep);

    std::istringstream stream(kod);
    std::string linia;
    float lineY = Layout::BOT_Y + 42.f;
    const float lineH = 18.f;
    const float maxY  = Layout::BOT_Y + Layout::BOT_H - 10.f;

    while (std::getline(stream, linia) && lineY + lineH < maxY) {
        sf::Text line = makeText(*czcionka, linia, 13, CLR_CODE_TXT);
        line.setPosition(sf::Vector2f{14.f, lineY});
        window.draw(line);
        lineY += lineH;
    }
}

void InterfejsUzytkownika::rysujPanelZlozonosci(sf::RenderWindow& window,
                                                  const InformacjeAlgorytmu& info) const {
    if (!czcionka) return;

    sf::RectangleShape tlo({ Layout::WIN_W - Layout::DIVIDER_X, Layout::BOT_H });
    tlo.setPosition(sf::Vector2f{Layout::DIVIDER_X, Layout::BOT_Y});
    tlo.setFillColor(CLR_PANEL_BG);
    window.draw(tlo);

    sf::RectangleShape sep({ 1.f, Layout::BOT_H });
    sep.setPosition(sf::Vector2f{Layout::DIVIDER_X, Layout::BOT_Y});
    sep.setFillColor(CLR_DIVIDER);
    window.draw(sep);

    float y = Layout::BOT_Y + 10.f;
    const float lx = Layout::DIVIDER_X + 20.f;

    {
        sf::Text hdr = makeText(*czcionka, "ZLOZONOSC OBLICZENIOWA", 14, CLR_HDR);
        setBoldStyle(hdr);
        hdr.setPosition(sf::Vector2f{lx, y});
        window.draw(hdr);
        y += 28.f;
    }

    {
        sf::RectangleShape hl({ Layout::WIN_W - Layout::DIVIDER_X - 40.f, 1.f });
        hl.setPosition(sf::Vector2f{lx, y});
        hl.setFillColor(CLR_DIVIDER);
        window.draw(hl);
        y += 12.f;
    }

    auto rysujWiersz = [&](const std::string& label, const std::string& wartosc,
                            sf::Color kolor = CLR_TEXT) {
        sf::Text lbl = makeText(*czcionka, label, 13, sf::Color(100, 100, 115));
        lbl.setPosition(sf::Vector2f{lx, y});
        window.draw(lbl);

        sf::Text val = makeText(*czcionka, wartosc, 13, kolor);
        setBoldStyle(val);
        val.setPosition(sf::Vector2f{lx + 215.f, y});
        window.draw(val);
        y += 24.f;
    };

    rysujWiersz("Zlozonosc czasowa:",  "");
    rysujWiersz("  Najlepsza:",  info.getNajlepsza());
    rysujWiersz("  Srednia:",    info.getSrednia());
    rysujWiersz("  Najgorsza:",  info.getNajgorsza());
    y += 18.f;
    rysujWiersz("Zlozonosc pamieciowa:", info.getPamieci());
}

void InterfejsUzytkownika::rysujPanelKrokow(sf::RenderWindow& window,
                                              const std::vector<std::string>& opisy,
                                              int obecnyKrok) {
    if (!czcionka) return;

    sf::RectangleShape overlay({ Layout::WIN_W, Layout::WIN_H });
    overlay.setPosition(sf::Vector2f{0.f, 0.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 120));
    window.draw(overlay);

    const float popupX = 0.f;
    const float popupY = 10.f;
    const float popupW = 1680.f;
    const float popupH = 1050.f;

    sf::RectangleShape panel({ popupW, popupH });
    panel.setPosition(sf::Vector2f{popupX, popupY});
    panel.setFillColor(sf::Color(245, 245, 248));
    panel.setOutlineThickness(1.f);
    panel.setOutlineColor(CLR_BTN_BDR);
    window.draw(panel);

    sf::Text hdr = makeText(*czcionka, "HISTORIA", 16, CLR_HDR);
    setBoldStyle(hdr);
    hdr.setPosition(sf::Vector2f{popupX + 20.f, popupY + 16.f});
    window.draw(hdr);


    sf::RectangleShape closeBtn({ 86.f, 28.f });
    closeBtn.setPosition(sf::Vector2f{popupX + popupW - 106.f, popupY + 12.f});
    closeBtn.setFillColor(CLR_BTN);
    closeBtn.setOutlineThickness(1.f);
    closeBtn.setOutlineColor(CLR_BTN_BDR);
    window.draw(closeBtn);

    sf::Text closeTxt = makeText(*czcionka, "Zamknij", 12, CLR_TEXT);
    closeTxt.setPosition(sf::Vector2f{popupX + popupW - 86.f, popupY + 18.f});
    window.draw(closeTxt);

    sf::RectangleShape sep({ popupW - 40.f, 1.f });
    sep.setPosition(sf::Vector2f{popupX + 20.f, popupY + 76.f});
    sep.setFillColor(CLR_DIVIDER);
    window.draw(sep);

    if (opisy.empty()) {
        sf::Text empty = makeText(*czcionka, "Brak historii do wyswietlenia", 13, CLR_TEXT);
        empty.setPosition(sf::Vector2f{popupX + 20.f, popupY + 100.f});
        window.draw(empty);
        return;
    }

    const int visibleCount = 16;
    const int maxStart = std::max(0, static_cast<int>(opisy.size()) - visibleCount);
    historiaScroll = std::clamp(historiaScroll, 0, maxStart);

    float y = popupY + 94.f;
    const float lineStep = 21.f;
    for (int i = historiaScroll; i < static_cast<int>(opisy.size()); ++i) {
        if (y > popupY + popupH - 18.f) break;
        sf::Color kolor = (i == obecnyKrok) ? sf::Color(40, 70, 160) : CLR_TEXT;
        sf::Text wiersz = makeText(*czcionka, std::to_string(i + 1) + ". " + opisy[i], 13, kolor);
        if (i == obecnyKrok) {
            setBoldStyle(wiersz);
        }
        wiersz.setPosition(sf::Vector2f{popupX + 20.f, y});
        window.draw(wiersz);
        y += lineStep;
    }
}

void InterfejsUzytkownika::RysujInterfejs(sf::RenderWindow& window,
                                           const InformacjeAlgorytmu& info,
                                           StanProgramu stan,
                                           const std::string& nazwaAlgorytmu,
                                           const std::vector<std::string>& historiaOpisow,
                                           int obecnyKrok) {
    if (!czcionka) return;

    sf::RectangleShape ctrlBg({
        static_cast<float>(Layout::WIN_W),
        CTRL_H
    });
    ctrlBg.setPosition({0.f, CTRL_Y});
    ctrlBg.setFillColor(CLR_CTRL_BG);
    window.draw(ctrlBg);

    sf::RectangleShape sepTop({ Layout::WIN_W, 1.f });
    sepTop.setPosition(sf::Vector2f{0.f, CTRL_Y});
    sepTop.setFillColor(CLR_DIVIDER);
    window.draw(sepTop);

    btnPoprzedni.wlaczony = (obecnyKrok > 0);
    btnNastepny.wlaczony  = (stan != StanProgramu::AutomatyczneSortowanie);
    btnStop.wlaczony      = (stan == StanProgramu::AutomatyczneSortowanie);

    btnPoprzedni.rysuj(window);
    btnNastepny.rysuj(window);

    btnStop.rysuj(window);

    btnAutoSort.wlaczony = (stan != StanProgramu::AutomatyczneSortowanie);
    btnAutoSort.rysuj(window);

    btnZapisz.wlaczony = true;
    btnZapisz.rysuj(window);

    btnReset.rysuj(window);
    btnHistoria.rysuj(window);

    {
        sf::Text lbl = makeText(*czcionka, "Predkosc:", 11, sf::Color(80, 80, 85));
        lbl.setPosition(sf::Vector2f{SLIDER_X, CTRL_Y + 6.f});
        window.draw(lbl);
    }
    window.draw(suwakTlo);
    window.draw(suwakKursor);

    {
        char buf[8];
        std::snprintf(buf, sizeof(buf), "%.2f x", predkosc);
        sf::Text val = makeText(*czcionka, buf, 11, CLR_TEXT);
        val.setPosition(sf::Vector2f{SLIDER_X + SLIDER_W + 6.f, CTRL_Y + 6.f});
        window.draw(val);
    }

    btnPrevAlgo.rysuj(window);
    btnNextAlgo.rysuj(window);

    {
        const float algoX     = btnPrevAlgo.tlo.getPosition().x + btnPrevAlgo.tlo.getSize().x + 6.f;
        const float algoW     = btnNextAlgo.tlo.getPosition().x - algoX - 6.f;
        const float BTN_H_val = btnPrevAlgo.tlo.getSize().y;
        const float BTN_Y_val = btnPrevAlgo.tlo.getPosition().y;

        sf::RectangleShape algoBg({ algoW, BTN_H_val });
        algoBg.setPosition(sf::Vector2f{algoX, BTN_Y_val});
        algoBg.setFillColor(CLR_BTN);
        algoBg.setOutlineThickness(1.f);
        algoBg.setOutlineColor(CLR_BTN_BDR);
        window.draw(algoBg);

        if (labelAlgorytm) {
            labelAlgorytm->setString(nazwaAlgorytmu);
            sf::FloatRect lb = labelAlgorytm->getLocalBounds();
            labelAlgorytm->setPosition(sf::Vector2f{
                algoX + (algoW - rectWidth(lb)  - rectLeft(lb)) / 2.f,
                BTN_Y_val + (BTN_H_val - rectHeight(lb) - rectTop(lb)) / 2.f});
            window.draw(*labelAlgorytm);
        }
    }

    btnAutoSort.wlaczony = (stan != StanProgramu::AutomatyczneSortowanie);
    btnStop.wlaczony = (stan == StanProgramu::AutomatyczneSortowanie);
    btnAutoSort.rysuj(window);
    btnStop.rysuj(window);
    btnReset.rysuj(window);
    btnHistoria.rysuj(window);

    if (stan == StanProgramu::Historia) {
        rysujPanelKrokow(window, historiaOpisow, obecnyKrok);
    } else {
        rysujPanelKodu(window, info.getKod());
        rysujPanelZlozonosci(window, info);
    }
}
