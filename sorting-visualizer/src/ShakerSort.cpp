#include "ShakerSort.hpp"
#include <algorithm>

void ShakerSort::Sortuj() {
    historia.clear();
    obecnyKrok = -1;

    std::vector<int> tmp = dane;
    const int n = static_cast<int>(tmp.size());

    auto zapiszKrok = [&](int a, int b, const std::string& opis) {
        historia.push_back(KrokSortowania{tmp, a, b, opis});
    };

    bool swapped = true;
    int left = 0;
    int right = n - 1;

    while (swapped) {
        swapped = false;

        for (int i = left; i < right; ++i) {
            zapiszKrok(i, i + 1,
                       "Porownanie: arr[" + std::to_string(i) + "]=" +
                       std::to_string(tmp[i]) + " z arr[" +
                       std::to_string(i + 1) + "]=" + std::to_string(tmp[i + 1]));
            if (tmp[i] > tmp[i + 1]) {
                std::swap(tmp[i], tmp[i + 1]);
                swapped = true;
                zapiszKrok(i, i + 1, "Zamiana sasiadow");
            }
        }

        if (!swapped) break;
        swapped = false;
        --right;

        for (int i = right; i > left; --i) {
            zapiszKrok(i - 1, i,
                       "Porownanie: arr[" + std::to_string(i - 1) + "]=" +
                       std::to_string(tmp[i - 1]) + " z arr[" +
                       std::to_string(i) + "]=" + std::to_string(tmp[i]));
            if (tmp[i - 1] > tmp[i]) {
                std::swap(tmp[i - 1], tmp[i]);
                swapped = true;
                zapiszKrok(i - 1, i, "Zamiana sasiadow");
            }
        }
        ++left;
    }

    zapiszKrok(-1, -1, "Sortowanie zakonczone");
}

void ShakerSort::Wizualizuj() {
}

void ShakerSort::NastepnyKrok() {
    if (historia.empty()) {
        Sortuj();
    }
    if (obecnyKrok < 0) {
        ++obecnyKrok;
    } else if (!CzySkonczone()) {
        ++obecnyKrok;
    }
}

InformacjeAlgorytmu ShakerSort::getInformacje() const {
    const std::string kod =
        "void shakerSort(int arr[], int n) {\n"
        "  bool swapped = true;\n"
        "  int left = 0, right = n - 1;\n"
        "  while (swapped) {\n"
        "    swapped = false;\n"
        "    for (int i = left; i < right; ++i) {\n"
        "      if (arr[i] > arr[i + 1]) {\n"
        "        swap(arr[i], arr[i + 1]);\n"
        "        swapped = true;\n"
        "      }\n"
        "    }\n"
        "    --right;\n"
        "    for (int i = right; i > left; --i) {\n"
        "      if (arr[i - 1] > arr[i]) {\n"
        "        swap(arr[i - 1], arr[i]);\n"
        "        swapped = true;\n"
        "      }\n"
        "    }\n"
        "    ++left;\n"
        "  }\n"
        "}";

    return InformacjeAlgorytmu(kod, "O(n)", "O(n^2)", "O(n^2)", "O(1)");
}

std::string ShakerSort::getNazwa() const {
    return "Sortowanie koktajlowe";
}
