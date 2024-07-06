#include "ware.hpp"
#include <stdexcept>

Ware::Ware(const std::string& name, float price, int units)
    : name(name), price(price), units(units) {}

std::string Ware::getName() const {
    return name;
}

float Ware::getPrice() const {
    return price;
}

int Ware::getUnits() const {
    return units;
}

void Ware::setPrice(float price) {
    if (price < 0) {
        throw std::invalid_argument("Preis darf nicht negativ sein");
    }
    this->price = price;
}

void Ware::addUnits(int additionalUnits) {
    if (additionalUnits < 0) {
        throw std::invalid_argument("Anzahl darf nicht negativ sein");
    }
    units += additionalUnits;
}

void Ware::removeUnits(int unitsToRemove) {
    if (unitsToRemove < 0) {
        throw std::invalid_argument("Anzahl darf nicht negativ sein");
    }
    if (unitsToRemove > units) {
        throw std::invalid_argument("Es duerfen nicht mehr Einheiten entfernt werden als vorhanden sind");
    }
    units -= unitsToRemove;
}
