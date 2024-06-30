#pragma once

#include <string>
#include <ctime>

class Ware {
private:
    std::string name;
    int anzahl;
    double aktuellerWert;
    std::time_t letzteAktualisierung;

public:
    // Constructor
    Ware(const std::string& name = "", int anzahl = 0, double aktuellerWert = 0.0, std::time_t letzteAktualisierung = std::time(nullptr));

    // Getters
    const std::string& getName() const;
    int getAnzahl() const;
    double getAktuellerWert() const;
    std::time_t getLetzteAktualisierung() const;

    // Setters
    void setAnzahl(int anzahl);
    void setAktuellerWert(double aktuellerWert);
    void setLetzteAktualisierung(std::time_t letzteAktualisierung);
};
