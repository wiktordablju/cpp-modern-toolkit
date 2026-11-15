#include <iostream>
#include <filesystem>
#include <string>
#include <map>

namespace fs = std::filesystem;

int main() {

    // Path inspection
    std::cout << "Path inspection" <<std::endl;
    fs::path sampleFile = "sample-data/plik.txt";
    std::cout << "nazwa pliku: " << sampleFile.filename() << std::endl;
    std::cout << "rozszerzenie pliku: " <<  sampleFile.extension() << std::endl;
    std::cout << "katalog nadrzedny pliku: " << sampleFile.parent_path() << std::endl;
    std::cout << "czy sciezka jest absolutna?: " <<  sampleFile.is_absolute() << std::endl;
    std::cout << "czy sciezka jest relatywna?: " << sampleFile.is_relative() << std::endl;
    std::cout << " -----------------------------" << std::endl;

    // Extension counts
    std::cout << "Extension counts" <<std::endl;
    fs::path countRoot = "sample-data";
    if (!fs::exists(countRoot)) {
        std::cout << "katalog nie istnieje" << std::endl;
        return 1;
    }

    auto opcje = fs::directory_options::skip_permission_denied;
    std::map<std::string, int> zliczenia;

    for (const auto& element : fs::recursive_directory_iterator(countRoot, opcje)) {
        if (element.is_regular_file()) {
            std::string rozszerzenie = element.path().extension().string();
            if (rozszerzenie.empty()) {
                rozszerzenie = "brak rozszerzenia";
            }
            zliczenia[rozszerzenie]++;
        }
    }

    std::cout << "rozszerzenia:" << std::endl;
    for (const auto& [roz, wystapienia] : zliczenia) {
        std::cout << roz << ": " << wystapienia << std::endl;
    }

    std::cout << " -----------------------------" << std::endl;

    // Temporary file sizes
    std::cout << "Temporary file sizes" <<std::endl;
    fs::path sizeRoot = "sample-data";
    if (!fs::exists(sizeRoot)) {
        std::cout << "katalog nie istnieje" << std::endl;
        return 1;
    }

    double zwolnione = 0;

    for (const auto& element : fs::recursive_directory_iterator(sizeRoot, opcje)) {
        if (element.is_regular_file()) {
            std::string rozszerzenie = element.path().extension().string();
            if (rozszerzenie == ".tmp" || rozszerzenie == ".log") {
                // fs::remove(element.path()); // usunie pliki po odkomentowaniu
                zwolnione += element.file_size();
            }
        }
    }

    std::cout << "zwolnione miejsce w kilobajtach: " << zwolnione / 1024 << " KB" << std::endl;
    std::cout << "zwolnione miejsce w megabajtach: " << zwolnione / (1024 * 1024) << " MB" << std::endl;


    std::cout << " -----------------------------" << std::endl;


    return 0;
}