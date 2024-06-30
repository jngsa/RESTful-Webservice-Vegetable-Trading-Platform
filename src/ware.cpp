#include "ware.hpp"

Ware::Ware(const std::string& name, int anzahl, double aktuellerWert, std::time_t letzteAktualisierung)
    : name(name), anzahl(anzahl), aktuellerWert(aktuellerWert), letzteAktualisierung(letzteAktualisierung) {
}

const std::string& Ware::getName() const {
    return name;
}

int Ware::getAnzahl() const {
    return anzahl;
}

double Ware::getAktuellerWert() const {
    return aktuellerWert;
}

std::time_t Ware::getLetzteAktualisierung() const {
    return letzteAktualisierung;
}

void Ware::setAnzahl(int anzahl) {
    this->anzahl = anzahl;
}

void Ware::setAktuellerWert(double aktuellerWert) {
    this->aktuellerWert = aktuellerWert;
}

void Ware::setLetzteAktualisierung(std::time_t letzteAktualisierung) {
    this->letzteAktualisierung = letzteAktualisierung;
}
