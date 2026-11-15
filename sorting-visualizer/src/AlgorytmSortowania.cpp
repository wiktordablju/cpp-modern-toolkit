#include "AlgorytmSortowania.hpp"

void AlgorytmSortowania::Reset() {
    historia.clear();
    obecnyKrok = -1;
}

void AlgorytmSortowania::SetDane(const std::vector<int>& nowyDane) {
    dane = nowyDane;
    Reset();
}

const std::vector<int>& AlgorytmSortowania::GetDane() const {
    if (!historia.empty() && obecnyKrok >= 0 && obecnyKrok < static_cast<int>(historia.size())) {
        return historia[obecnyKrok].stanTablicy;
    }
    return dane;
}

const std::vector<KrokSortowania>& AlgorytmSortowania::GetHistoria() const {
    return historia;
}

int AlgorytmSortowania::GetObecnyKrok() const {
    return obecnyKrok;
}

bool AlgorytmSortowania::CzySkonczone() const {
    return !historia.empty() &&
           obecnyKrok >= 0 &&
           obecnyKrok >= static_cast<int>(historia.size()) - 1;
}

void AlgorytmSortowania::PoprzedniKrok() {
    if (obecnyKrok > 0) {
        --obecnyKrok;
    } else if (obecnyKrok == 0) {
        obecnyKrok = -1;
    }
}
