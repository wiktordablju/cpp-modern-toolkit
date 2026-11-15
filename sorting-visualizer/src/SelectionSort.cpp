#include "SelectionSort.hpp"
#include <algorithm>

void SelectionSort::Sortuj() {
    historia.clear();
    obecnyKrok = -1;

    std::vector<int> tmp = dane;
    const int n = static_cast<int>(tmp.size());

    auto zapiszKrok = [&](int a, int b, const std::string& opis) {
        historia.push_back(KrokSortowania{tmp, a, b, opis});
    };

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            zapiszKrok(minIndex, j,
                       "Porownanie: arr[" + std::to_string(minIndex) + "]=" +
                       std::to_string(tmp[minIndex]) + " z arr[" +
                       std::to_string(j) + "]=" + std::to_string(tmp[j]));
            if (tmp[j] < tmp[minIndex]) {
                minIndex = j;
                zapiszKrok(i, minIndex, "Nowe minimum na pozycji " + std::to_string(minIndex));
            }
        }

        if (minIndex != i) {
            std::swap(tmp[i], tmp[minIndex]);
            zapiszKrok(i, minIndex,
                       "Zamiana: arr[" + std::to_string(i) + "] <-> arr[" +
                       std::to_string(minIndex) + "]");
        }
    }

    zapiszKrok(-1, -1, "Sortowanie zakonczone");
}

void SelectionSort::Wizualizuj() {
}

void SelectionSort::NastepnyKrok() {
    if (historia.empty()) {
        Sortuj();
    }
    if (obecnyKrok < 0) {
        ++obecnyKrok;
    } else if (!CzySkonczone()) {
        ++obecnyKrok;
    }
}

InformacjeAlgorytmu SelectionSort::getInformacje() const {
    const std::string kod =
        "void selectionSort(int arr[], int n) {\n"
        "  for (int i = 0; i < n - 1; ++i) {\n"
        "    int minIndex = i;\n"
        "    for (int j = i + 1; j < n; ++j) {\n"
        "      if (arr[j] < arr[minIndex]) {\n"
        "        minIndex = j;\n"
        "      }\n"
        "    }\n"
        "    swap(arr[i], arr[minIndex]);\n"
        "  }\n"
        "}";

    return InformacjeAlgorytmu(kod, "O(n^2)", "O(n^2)", "O(n^2)", "O(1)");
}

std::string SelectionSort::getNazwa() const {
    return "Sortowanie przez wybor";
}
