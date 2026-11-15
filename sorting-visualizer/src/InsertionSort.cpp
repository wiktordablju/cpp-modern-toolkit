#include "InsertionSort.hpp"

void InsertionSort::Sortuj() {
    historia.clear();
    obecnyKrok = -1;

    std::vector<int> tmp = dane;
    const int n = static_cast<int>(tmp.size());

    auto zapiszKrok = [&](int a, int b, const std::string& opis) {
        historia.push_back(KrokSortowania{tmp, a, b, opis});
    };

    for (int i = 1; i < n; ++i) {
        int key = tmp[i];
        int j = i - 1;
        zapiszKrok(i, j, "Wybór elementu " + std::to_string(key));

        while (j >= 0 && tmp[j] > key) {
            zapiszKrok(j, i, "Przesuniecie: arr[" + std::to_string(j) + "]=" + std::to_string(tmp[j]) +
                                 " w prawo");
            tmp[j + 1] = tmp[j];
            --j;
        }

        tmp[j + 1] = key;
        zapiszKrok(j + 1, i, "Wstawienie elementu na pozycje " + std::to_string(j + 1));
    }

    zapiszKrok(-1, -1, "Sortowanie zakonczone");
}

void InsertionSort::Wizualizuj() {
}

void InsertionSort::NastepnyKrok() {
    if (historia.empty()) {
        Sortuj();
    }
    if (obecnyKrok < 0) {
        ++obecnyKrok;
    } else if (!CzySkonczone()) {
        ++obecnyKrok;
    }
}

InformacjeAlgorytmu InsertionSort::getInformacje() const {
    const std::string kod =
        "void insertionSort(int arr[], int n) {\n"
        "  for (int i = 1; i < n; ++i) {\n"
        "    int key = arr[i];\n"
        "    int j = i - 1;\n"
        "    while (j >= 0 && arr[j] > key) {\n"
        "      arr[j + 1] = arr[j];\n"
        "      --j;\n"
        "    }\n"
        "    arr[j + 1] = key;\n"
        "  }\n"
        "}";

    return InformacjeAlgorytmu(kod, "O(n)", "O(n^2)", "O(n^2)", "O(1)");
}

std::string InsertionSort::getNazwa() const {
    return "Sortowanie przez wstawianie";
}
