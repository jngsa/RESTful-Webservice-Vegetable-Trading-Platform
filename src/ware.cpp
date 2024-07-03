#include "ware.hpp"

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
    this->price = price;
}

void Ware::addUnits(int additionalUnits) {
    units += additionalUnits;
}

void Ware::removeUnits(int unitsToRemove) {
    units -= unitsToRemove;
    if (units < 0) {
        units = 0;
    }
}
