#include "ware.hpp"

Ware::Ware(const std::string& name, double aktuellerWert)
    : name(name), aktuellerWert(aktuellerWert) {
    // Constructor definition
}

std::string Ware::getName() const {
    return name;
}

double Ware::getPreis() const {
    return aktuellerWert;
}
