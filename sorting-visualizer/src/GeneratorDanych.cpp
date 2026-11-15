#include "GeneratorDanych.hpp"
#include <random>
#include <stdexcept>

std::vector<int> GeneratorDanych::GenerujDane(int ilosc, int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    std::vector<int> wynik;
    wynik.reserve(static_cast<size_t>(ilosc));
    for (int i = 0; i < ilosc; ++i) {
        wynik.push_back(dist(gen));
    }
    return wynik;
}
