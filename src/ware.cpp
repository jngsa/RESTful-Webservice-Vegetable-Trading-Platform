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

void Ware::updateUnits(int anzahl) {
    units += anzahl;
}
