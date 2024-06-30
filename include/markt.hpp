// Marktplatz.hpp

#pragma once

#include "Nutzer.hpp"
#include "Konto.hpp"
#include "Ware.hpp"
#include <unordered_map>

class Marktplatz {
public:
    void nutzerHinzufuegen(const Nutzer& nutzer);
    void kontoHinzufuegen(const Konto& konto);
    void wareHinzufuegen(const Ware& ware);

    Nutzer nutzerAbrufen(int nutzerID) const;
    Konto kontoAbrufen(int nutzerID) const;
    Ware wareAbrufen(int warenID) const;

    void wareKaufen(int nutzerID, int warenID, int menge);
    void wareVerkaufen(int nutzerID, int warenID, int menge);

    void handelswerteAktualisieren(double tendenz, double standardabweichung, double zeitschritt);
    const std::unordered_map<int, Ware>& alleWarenAbrufen() const;

private:
    std::unordered_map<int, Nutzer> nutzer;
    std::unordered_map<int, Konto> konten;
    std::unordered_map<int, Ware> waren;
};
