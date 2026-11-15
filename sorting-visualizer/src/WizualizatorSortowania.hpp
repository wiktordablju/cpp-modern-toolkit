#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <future>
#include "StanProgramu.hpp"
#include "AlgorytmSortowania.hpp"
#include "RendererHistogramu.hpp"
#include "InterfejsUzytkownika.hpp"

class WizualizatorSortowania {
private:
    sf::RenderWindow okno;
    sf::Font czcionka;

    std::map<std::string, std::unique_ptr<AlgorytmSortowania>> algorytmy;
    std::vector<std::string> listaAlgorytmow;
    int indeksAlgorytmu = 0;
    AlgorytmSortowania* algorytm = nullptr;

    RendererHistogramu  rendererHistogramu;
    InterfejsUzytkownika interfejs;

    StanProgramu stanProgramu = StanProgramu::Bezczynnosc;
    bool pelnyEkran = false;
    sf::View widokBazowy;
    std::future<void> zapisHistoriiFuture;

    sf::Clock zegarAnimacji;   

    bool wczytajCzcionke();
    void inicjalizujAlgorytmy();
    void generujNoweDane();
    void ustawAlgorytm(int indeks);
    void ustawTrybOkna(bool fullscreen);
    void ustawWidokBazowy();
    void zapiszHistorieDoPliku(const std::vector<std::string>& opisy,
                               const std::string& nazwaAlgorytmu);

    void obsluzAkcje(AkcjaUI akcja);

public:
    WizualizatorSortowania();

    void Uruchom();
    void ObsluzZdarzenia();
    void Aktualizuj(float dt);
    void Renderuj();
};
