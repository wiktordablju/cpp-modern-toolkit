#include "BubbleSort.hpp"
#include <algorithm>

void BubbleSort::Sortuj() {
    historia.clear();
    obecnyKrok = -1;

    std::vector<int> tmp = dane;
    const int n = static_cast<int>(tmp.size());

    auto zapiszKrok = [&](int a, int b, const std::string& opis) {
        KrokSortowania k;
        k.stanTablicy = tmp;
        k.indeksA = a;
        k.indeksB = b;
        k.opisOperacji = opis;
        historia.push_back(k);
    };

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            zapiszKrok(j, j + 1,
                "Porownanie: arr[" + std::to_string(j) + "]=" +
                std::to_string(tmp[j]) + " z arr[" +
                std::to_string(j + 1) + "]=" + std::to_string(tmp[j + 1]));

            if (tmp[j] > tmp[j + 1]) {
                std::swap(tmp[j], tmp[j + 1]);
                zapiszKrok(j, j + 1,
                    "Zamiana: arr[" + std::to_string(j) + "] <-> arr[" +
                    std::to_string(j + 1) + "]");
            }
        }
    }
    zapiszKrok(-1, -1, "Sortowanie zakonczone");
}

void BubbleSort::Wizualizuj() {
}

void BubbleSort::NastepnyKrok() {
    if (historia.empty()) {
        Sortuj();
    }
    if (obecnyKrok < 0) {
        ++obecnyKrok;
    } else if (!CzySkonczone()) {
        ++obecnyKrok;
    }
}

InformacjeAlgorytmu BubbleSort::getInformacje() const {
    const std::string kod =
        "void bubbleSort(int arr[], int n) {\n"
        "  for (int i = 0; i < n-1; i++) {\n"
        "    for (int j = 0; j < n-i-1; j++) {\n"
        "      if (arr[j] > arr[j+1]) {\n"
        "        swap(arr[j], arr[j+1]);\n"
        "      }\n"
        "    }\n"
        "  }\n"
        "}";

    return InformacjeAlgorytmu(
        kod,
        "O(n)",
        "O(n^2)",
        "O(n^2)",
        "O(1)"
    );
}

std::string BubbleSort::getNazwa() const {
    return "Sortowanie babelkowe";
}
