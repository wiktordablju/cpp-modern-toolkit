#include "InformacjeAlgorytmu.hpp"
#include <utility>

InformacjeAlgorytmu::InformacjeAlgorytmu(std::string kod, std::string najlepsza, std::string srednia, std::string najgorsza, std::string pamieci) : kodAlgorytmu(std::move(kod)), zlozonosc_najlepsza(std::move(najlepsza)), zlozonosc_srednia(std::move(srednia)), zlozonosc_najgorsza(std::move(najgorsza)), zlozonosc_pamieci(std::move(pamieci)){}
const std::string& InformacjeAlgorytmu::getKod()       const { return kodAlgorytmu; }
const std::string& InformacjeAlgorytmu::getNajlepsza() const { return zlozonosc_najlepsza; }
const std::string& InformacjeAlgorytmu::getSrednia()   const { return zlozonosc_srednia; }
const std::string& InformacjeAlgorytmu::getNajgorsza() const { return zlozonosc_najgorsza; }
const std::string& InformacjeAlgorytmu::getPamieci()   const { return zlozonosc_pamieci; }
