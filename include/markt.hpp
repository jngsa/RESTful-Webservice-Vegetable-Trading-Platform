#pragma once

#include <unordered_map>
#include "konto.hpp"
#include "ware.hpp"

class Markt {
private:
    std::unordered_map<int, NutzerKonto> nutzerkonten;
    std::unordered_map<int, Ware> waren;

public:
    // Methods to handle transactions
    void wareKaufen(int nutzerID, int warenID, int menge, double gesamtpreis);
    void wareVerkaufen(int nutzerID, int warenID, int menge, double angebotspreis);
    void aktualisiereHandelswerte(double inflationsrate, double wechselkurs, double zinssatz);
};

