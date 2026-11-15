#include "WizualizatorSortowania.hpp"
#include "BubbleSort.hpp"
#include "InsertionSort.hpp"
#include "GeneratorDanych.hpp"
#include "SelectionSort.hpp"
#include "ShakerSort.hpp"
#include "RendererHistogramu.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <ranges>
#include <regex>
#include <sstream>
#include <vector>
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

inline constexpr std::array<const char*, 4> FONT_PATHS = {
    "/System/Library/Fonts/Menlo.ttc",
};


WizualizatorSortowania::WizualizatorSortowania(): okno(sf::VideoMode::getDesktopMode(),"Wizualizator Algorytmow Sortowania", sf::Style::Default)
{
    ustawWidokBazowy();
    okno.setFramerateLimit(60);

    if (!wczytajCzcionke()) {
    }

    rendererHistogramu.setCzcionka(czcionka);
    interfejs.setCzcionka(czcionka);
    interfejs.inicjalizuj();
    inicjalizujAlgorytmy();
    generujNoweDane();
}

void WizualizatorSortowania::ustawWidokBazowy() {
    widokBazowy = sf::View();
    widokBazowy.setCenter(sf::Vector2f{static_cast<float>(Layout::WIN_W) / 2.f, static_cast<float>(Layout::WIN_H) / 2.f});
    widokBazowy.setSize(sf::Vector2f{static_cast<float>(Layout::WIN_W), static_cast<float>(Layout::WIN_H)});
    okno.setView(widokBazowy);
}

bool WizualizatorSortowania::wczytajCzcionke() {
    for (const auto& path : FONT_PATHS) {
        if (czcionka.openFromFile(path)) {
            return true;
        }
    }
    return false;
}

void WizualizatorSortowania::inicjalizujAlgorytmy() {
    algorytmy["Sortowanie babelkowe"] = std::make_unique<BubbleSort>();
    algorytmy["Sortowanie przez wybor"] = std::make_unique<SelectionSort>();
    algorytmy["Sortowanie przez wstawianie"] = std::make_unique<InsertionSort>();
    algorytmy["Sortowanie koktajlowe"] = std::make_unique<ShakerSort>();

    listaAlgorytmow.reserve(algorytmy.size());
    std::ranges::transform(algorytmy, std::back_inserter(listaAlgorytmow),[](const auto& element) { return element.first; });
    ustawAlgorytm(0);
}

void WizualizatorSortowania::generujNoweDane() {
    if (!algorytm) return;
    auto dane = GeneratorDanych::GenerujDane(10, 1, 50);
    algorytm->SetDane(dane);
    stanProgramu = StanProgramu::Bezczynnosc;
}

void WizualizatorSortowania::ustawAlgorytm(int indeks) {
    indeksAlgorytmu = indeks;
    algorytm = algorytmy.at(listaAlgorytmow[indeks]).get();
    generujNoweDane();
}

void WizualizatorSortowania::zapiszHistorieDoPliku(const std::vector<std::string>& opisy, const std::string& nazwaAlgorytmu)
{
    std::filesystem::path katalog = "historia";
    std::filesystem::create_directories(katalog);

    std::regex niebezpieczne("[^A-Za-z0-9_-]+");
    std::string cleanName = std::regex_replace(nazwaAlgorytmu, niebezpieczne, "_");

    std::filesystem::path plik = katalog / (cleanName + ".txt");

    zapisHistoriiFuture = std::async(std::launch::async,[plik, opisy, nazwaAlgorytmu]() {

            std::ofstream out(plik);
            if (!out.is_open()) {
                return;
            }

            out << "Algorytm: " << nazwaAlgorytmu << "\n";
            out << "Liczba krokow: " << opisy.size() << "\n\n";

            for (size_t i = 0; i < opisy.size(); i++) {
                out << i + 1 << ". " << opisy[i] << "\n";
            }
        });
}


void WizualizatorSortowania::Uruchom() {
    zegarAnimacji.restart();
    sf::Clock zegar;

    while (okno.isOpen()) {
        float dt = zegar.restart().asSeconds();
        ObsluzZdarzenia();
        Aktualizuj(dt);
        Renderuj();
    }
}

void WizualizatorSortowania::ObsluzZdarzenia() {
    while (auto eventOpt = okno.pollEvent()) {
        const auto& event = *eventOpt;
        if (event.is<sf::Event::Closed>()) {
            okno.close();
            return;
        }
        if (event.is<sf::Event::Resized>()) {
            ustawWidokBazowy();
            continue;
        }
        if (event.is<sf::Event::KeyPressed>()) {
            const auto* k = event.getIf<sf::Event::KeyPressed>();
            if (k && k->code == sf::Keyboard::Key::Escape) {
                okno.close();
                return;
            }
        }

        AkcjaUI akcja = interfejs.ObsluzWejscie(event, okno, stanProgramu);
        obsluzAkcje(akcja);
    }

}

void WizualizatorSortowania::obsluzAkcje(AkcjaUI akcja) {
    if (!algorytm) return;

    switch (akcja) {
    case AkcjaUI::NastepnyKrok:
        stanProgramu = StanProgramu::ManualnieSortowanie;
        algorytm->NastepnyKrok();
        break;

    case AkcjaUI::PoprzedniKrok:
        stanProgramu = StanProgramu::ManualnieSortowanie;
        algorytm->PoprzedniKrok();
        break;

    case AkcjaUI::SortujAutomatycznie:
        stanProgramu = StanProgramu::AutomatyczneSortowanie;
        if (algorytm->GetObecnyKrok() < 0) {
            algorytm->NastepnyKrok();
            zegarAnimacji.restart();
        }
        break;

    case AkcjaUI::StopSortowanie:
        stanProgramu = StanProgramu::Bezczynnosc;
        break;

    case AkcjaUI::Reset:
        generujNoweDane();
        interfejs.resetHistorii();
        break;

    case AkcjaUI::ZapiszHistorie: {
        const auto& historia = algorytm->GetHistoria();
        std::vector<std::string> opisy;
        opisy.reserve(historia.size());
        std::ranges::transform(historia, std::back_inserter(opisy),[](const KrokSortowania& krok) { return krok.opisOperacji; });
        zapiszHistorieDoPliku(opisy, listaAlgorytmow[indeksAlgorytmu]);
        break;
    }

    case AkcjaUI::PokazHistorie:stanProgramu = (stanProgramu == StanProgramu::Historia) ? StanProgramu::Bezczynnosc : StanProgramu::Historia;
        if (stanProgramu == StanProgramu::Historia) {
            interfejs.resetHistorii();
        }
        break;

    case AkcjaUI::NastepnyAlgorytm:
        ustawAlgorytm((indeksAlgorytmu + 1) % static_cast<int>(listaAlgorytmow.size()));
        break;

    case AkcjaUI::PoprzedniAlgorytm:
        ustawAlgorytm((indeksAlgorytmu - 1 + static_cast<int>(listaAlgorytmow.size()))
                      % static_cast<int>(listaAlgorytmow.size()));
        break;

    default:
        break;
    }
}

void WizualizatorSortowania::Aktualizuj(float dt) {
    if (stanProgramu != StanProgramu::AutomatyczneSortowanie || !algorytm) {
        return;
    }

    const float predkosc = std::max(0.25f, interfejs.getPredkosc());
    const float interwal = 0.55f / predkosc;
    if (zegarAnimacji.getElapsedTime().asSeconds() >= interwal) {
        if (!algorytm->CzySkonczone()) {
            algorytm->NastepnyKrok();
        }
        zegarAnimacji.restart();

        if (algorytm->CzySkonczone()) {
            stanProgramu = StanProgramu::Bezczynnosc;
        }
    }
}

void WizualizatorSortowania::Renderuj() {
    if (!algorytm) return;

    okno.clear(sf::Color(240, 240, 242));

    const std::vector<int>& dane = algorytm->GetDane();
    int indA = -1, indB = -1;

    const auto& historia = algorytm->GetHistoria();
    int krok = algorytm->GetObecnyKrok();
    if (!historia.empty() && krok >= 0 && krok < static_cast<int>(historia.size())) {
        indA = historia[krok].indeksA;
        indB = historia[krok].indeksB;
    }

    rendererHistogramu.RysujSlupki(okno, dane, indA, indB);

    if (!historia.empty() && krok >= 0 && krok < static_cast<int>(historia.size())) {
        sf::Text opTekst = makeText(czcionka, "Krok " + std::to_string(krok + 1) + "/" + std::to_string(historia.size()) + ": " + historia[krok].opisOperacji, 12, sf::Color(80, 80, 90));
        opTekst.setPosition(sf::Vector2f{Layout::HIST_PAD_X, Layout::HIST_H - 16.f});
        okno.draw(opTekst);
    } else {
        sf::Text opTekst = makeText(czcionka, "Brak wykonanych krokow", 12, sf::Color(80, 80, 90));
        opTekst.setPosition(sf::Vector2f{Layout::HIST_PAD_X, Layout::HIST_H - 16.f});
        okno.draw(opTekst);
    }

    InformacjeAlgorytmu info = algorytm->getInformacje();

    std::vector<std::string> opisy;
    for (const auto& k : historia) opisy.push_back(k.opisOperacji);

    interfejs.RysujInterfejs(okno, info, stanProgramu, listaAlgorytmow[indeksAlgorytmu], opisy, krok);

    okno.display();
}
