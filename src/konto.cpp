#include "konto.hpp"
#include <stdexcept>

Konto::Konto(const std::string& benutzername, const std::string& passwort)
    : benutzername(benutzername), passwort(passwort), guthaben(1000.0f) {}

std::string Konto::getBenutzername() const {
    return benutzername;
}

std::string Konto::getPasswort() const {
    return passwort;
}

float Konto::getGuthaben() const {
    return guthaben;
}

std::unordered_map<std::string, Ware> Konto::getInventar() const {
    return inventar;
}

void Konto::sellWare(Bank& bank, const std::string& name, int units) {
    if (units <= 0) {
        throw std::invalid_argument("Units must be positive");
    }

    auto it = inventar.find(name);
    if (it != inventar.end() && it->second.getUnits() >= units) {
        float price = bank.getPrice(name);
        it->second.removeUnits(units);
        if (it->second.getUnits() == 0) {
            inventar.erase(it);
        }
        einzahlen(units * price);
    } else {
        throw std::invalid_argument("Not enough units in inventory or ware not found");
    }
}

void Konto::buyWare(Bank& bank, const std::string& name, int units) {
    if (units <= 0) {
        throw std::invalid_argument("Units must be positive");
    }

    float price = bank.getPrice(name);
    float totalPrice = price * units;

    if (getGuthaben() >= totalPrice) {
        auszahlen(totalPrice);
        auto it = inventar.find(name);
        if (it != inventar.end()) {
            it->second.addUnits(units);
        } else {
            inventar[name] = Ware(name, price, units);
        }
    } else {
        throw std::invalid_argument("Not enough guthaben to buy ware");
    }
}

void Konto::einzahlen(float betrag) {
    if (betrag > 0) {
        setGuthaben(getGuthaben() + betrag);
    }
}

bool Konto::auszahlen(float betrag) {
    if (betrag > 0 && getGuthaben() >= betrag) {
        setGuthaben(getGuthaben() - betrag);
        return true;
    }
    return false;
}

void Konto::setGuthaben(float betrag) {
    guthaben = betrag;
}
