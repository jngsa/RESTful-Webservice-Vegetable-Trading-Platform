#include "konto.hpp"
#include <algorithm> // for std::find_if
#include <stdexcept> // for std::runtime_error

Konto::Konto(const std::string& benutzername)
    : benutzername(benutzername), guthaben(1000.0f), nextOfferID(1) {
    // Initialize with 10 funny named stocks with 10 units each and price 0
    std::vector<std::string> funnyNames = {
        "Sonnenblumenöl", "Klausurzulassungen", "Einhornstaub", "Schneckenrennen",
        "Glückskekse", "Pizzalieferungen", "Regenbogenfarben", "Katzenbilder",
        "Traumfänger", "Einhornglitzer"
    };

    for (const auto& name : funnyNames) {
        inventar.push_back(Ware(name, 0.0f, 10));
    }
}

float Konto::getGuthaben() const {
    return guthaben;
}

std::vector<Ware> Konto::getInventar() const {
    return inventar;
}

std::vector<Ware> Konto::getOffers() const {
    return offers;
}

int Konto::getNextOfferID() const {
    return nextOfferID;
}

void Konto::einzahlen(float betrag) {
    if (betrag > 0) {
        guthaben += betrag;
    }
}

bool Konto::auszahlen(float betrag) {
    if (betrag > 0 && guthaben >= betrag) {
        guthaben -= betrag;
        return true;
    }
    return false;
}

void Konto::offerWare(const std::string& name, float price, int units) {
    auto it = std::find_if(inventar.begin(), inventar.end(),
                           [&name](const Ware& ware) { return ware.getName() == name; });

    if (it != inventar.end() && units > 0 && price >= 0.0f) {
        offers.push_back(Ware(name, price, units));
        ++nextOfferID;
    }
}

bool Konto::buyWare(int offerID, float& totalPrice) {
    auto it = std::find_if(offers.begin(), offers.end(),
                           [&offerID](const Ware& ware) { return ware.getUnits() > 0 && ware.getPrice() > 0.0f && offerID == ware.getPrice(); });

    if (it != offers.end()) {
        totalPrice = it->getPrice();
        if (guthaben >= totalPrice) {
            guthaben -= totalPrice;
            auto invIt = findWare(it->getName());
            if (invIt) {
                invIt->addUnits(it->getUnits());
            } else {
                inventar.push_back(*it);
            }
            it->removeUnits(it->getUnits());
            offers.erase(it);
            return true;
        }
    }
    return false;
}

void Konto::addUnits(const std::string& name, int units) {
    auto it = findWare(name);
    if (it) {
        it->addUnits(units);
    }
}

void Konto::removeUnits(const std::string& name, int units) {
    auto it = findWare(name);
    if (it) {
        it->removeUnits(units);
    }
}

Ware* Konto::findWare(const std::string& name) {
    auto it = std::find_if(inventar.begin(), inventar.end(),
                           [&name](const Ware& ware) { return ware.getName() == name; });
    if (it != inventar.end()) {
        return &(*it);
    }
    return nullptr;
}
