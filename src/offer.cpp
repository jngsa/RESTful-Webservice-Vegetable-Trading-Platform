#include "offer.hpp"

Offer::Offer(const std::string& benutzername, const Ware& ware, float price, int units)
    : benutzername(benutzername), ware(ware), price(price), units(units) {}

std::string Offer::getBenutzername() const {
    return benutzername;
}

Ware Offer::getWare() const {
    return ware;
}

float Offer::getPrice() const {
    return price;
}

int Offer::getUnits() const {
    return units;
}

void Offer::setUnits(int units) {
    this->units = units;
}
