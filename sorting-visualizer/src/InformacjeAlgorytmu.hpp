#pragma once
#include <string>

class InformacjeAlgorytmu {
private:
    std::string kodAlgorytmu;
    std::string zlozonosc_najlepsza;
    std::string zlozonosc_srednia;
    std::string zlozonosc_najgorsza;
    std::string zlozonosc_pamieci;

public:
    InformacjeAlgorytmu() = default;
    InformacjeAlgorytmu(std::string kod, std::string najlepsza, std::string srednia, std::string najgorsza, std::string pamieci);

    const std::string& getKod() const;
    const std::string& getNajlepsza() const;
    const std::string& getSrednia() const;
    const std::string& getNajgorsza() const;
    const std::string& getPamieci() const;
};
