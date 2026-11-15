#pragma once
#include <vector>
#include <string>
#include "KrokSortowania.hpp"
#include "InformacjeAlgorytmu.hpp"

class AlgorytmSortowania {
protected:
    std::vector<int> dane;
    std::vector<KrokSortowania> historia;
    int obecnyKrok = -1;

public:
    virtual ~AlgorytmSortowania() = default;

    virtual void Sortuj() = 0;
    virtual void Wizualizuj() = 0;
    virtual void NastepnyKrok() = 0;

    virtual InformacjeAlgorytmu getInformacje() const = 0;
    virtual std::string getNazwa() const = 0;

    void Reset();
    void SetDane(const std::vector<int>& nowyDane);

    const std::vector<int>& GetDane() const;
    const std::vector<KrokSortowania>& GetHistoria() const;
    int  GetObecnyKrok() const;
    bool CzySkonczone() const;

    void PoprzedniKrok();
};
