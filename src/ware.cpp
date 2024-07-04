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
        throw std::invalid_argument("Price cannot be negative");
    }
    this->price = price;
}

void Ware::addUnits(int additionalUnits) {
    if (additionalUnits < 0) {
        throw std::invalid_argument("Cannot add a negative number of units");
    }
    units += additionalUnits;
}

void Ware::removeUnits(int unitsToRemove) {
    if (unitsToRemove < 0) {
        throw std::invalid_argument("Cannot remove a negative number of units");
    }
    if (unitsToRemove > units) {
        throw std::invalid_argument("Cannot remove more units than available");
    }
    units -= unitsToRemove;
}
