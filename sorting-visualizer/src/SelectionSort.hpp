#pragma once
#include "AlgorytmSortowania.hpp"

class SelectionSort : public AlgorytmSortowania {
public:
    void Sortuj() override;
    void Wizualizuj() override;
    void NastepnyKrok() override;

    InformacjeAlgorytmu getInformacje() const override;
    std::string getNazwa() const override;
};
