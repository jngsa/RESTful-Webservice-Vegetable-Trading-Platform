#include "konto.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>

std::vector<Offer> Konto::offers;
std::unordered_map<std::string, Konto*> Konto::konten;

Konto::Konto(const std::string& benutzername, const std::string& passwort)
    : benutzername(benutzername), passwort(passwort), guthaben(1000.0f) {
    std::vector<std::string> namen = {
        "Sonnenblumenöl", "Klausurzulassungen", "Lidl", "Aldi",
        "Penny", "Edeka", "Rewe", "Boes",
        "Netto", "Ichweissnicht"
    };

    for (const auto& name : namen) {
        inventar.push_back(Ware(name, 0.0f, 10));
    }

    konten[benutzername] = this;
}

Konto* Konto::getKonto(const std::string& benutzername) {
    auto it = konten.find(benutzername);
    if (it != konten.end()) {
        return it->second; // Gibt das Konto mit dem eingegebenen Namen zurueck
    }
    return nullptr; // Konto nicht gefunden
}

std::string Konto::getBenutzername() const {
    return benutzername;
}

std::string Konto::getPasswort() const {
    return passwort;
}

float Konto::getGuthaben() const {
    return guthaben;
}

std::vector<Ware> Konto::getInventar() const {
    return inventar;
}

std::vector<Offer>& Konto::getAllOffers() {
    return offers;
}

void Konto::offerWare(const std::string& name, float price, int units) {
    auto it = std::find_if(inventar.begin(), inventar.end(),
                           [&name](const Ware& ware) { return ware.getName() == name; });

    if (it != inventar.end() && units > 0 && price >= 0.0f) {
        // prueft ob genug units im Inventar sind
        validateOffer(*it, units);

        getAllOffers().push_back(Offer(benutzername, *it, price, units));
    }
}

bool Konto::buyWare(size_t offerIndex, int units) {

    if (offerIndex >= getAllOffers().size()) {
        return false; // index existiert nicht
    }

    Offer& offer = getAllOffers()[offerIndex];

    float totalPrice = offer.getPrice() * units;

    // preuft ob genug Guthaben vorhanden ist
    if (getGuthaben() < totalPrice) {
        return false; 
    }

    if (units > offer.getUnits()) {
        return false; // zu viel units angefordert
    }

    Konto* sellerAccount = getKonto(offer.getBenutzername());

    if (!sellerAccount) {
        return false; // Verkaufer nicht gefunden
    }

    sellerAccount->einzahlen(totalPrice);

    // Inventar des Kaufers
    auszahlen(totalPrice);
    Ware* buyerWare = findWare(offer.getWare().getName());
    if (buyerWare) {
        buyerWare->addUnits(units);
    } else {
        inventar.push_back(Ware(offer.getWare().getName(), offer.getWare().getPrice(), units));
    }

    // Inventar des Verkaufers
    sellerAccount->removeUnits(offer.getWare().getName(), units);

    // offers array aktualisieren
    int remainingUnits = offer.getUnits() - units;
    if (remainingUnits > 0) {
        offer.setUnits(remainingUnits);
    } else {
        getAllOffers().erase(getAllOffers().begin() + offerIndex);
    }

    return true; // Kauf erfolgreich
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

void Konto::validateOffer(const Ware& ware, int units) {
    if (units > ware.getUnits()) {
        throw std::invalid_argument("Offer units exceed inventory units");
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
