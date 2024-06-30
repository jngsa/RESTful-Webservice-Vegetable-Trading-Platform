#include "markt.hpp"
#include "ware.hpp"
#include <algorithm>
#include <random>

Markt::Markt() {
    // Initialize with 10 stocks
    waren.push_back(std::make_shared<Ware>("Stock1", 50.0));
    waren.push_back(std::make_shared<Ware>("Stock2", 20.0));
    waren.push_back(std::make_shared<Ware>("Stock3", 200.0));
    waren.push_back(std::make_shared<Ware>("Stock4", 1000.0));
    waren.push_back(std::make_shared<Ware>("Stock5", 150.0));
    waren.push_back(std::make_shared<Ware>("Stock6", 500.0));
    waren.push_back(std::make_shared<Ware>("Stock7", 300.0));
    waren.push_back(std::make_shared<Ware>("Stock8", 800.0));
    waren.push_back(std::make_shared<Ware>("Stock9", 700.0));
    waren.push_back(std::make_shared<Ware>("Stock10", 900.0));
}

void Markt::addWare(std::shared_ptr<Ware> ware) {
    waren.push_back(ware);
}

void Markt::updatePreise() {
    for (auto& ware : waren) {
        ware->updatePreis();
    }
}

double Markt::getCurrentPrice(const std::string& wareName) const {
    for (const auto& ware : waren) {
        if (ware->getName() == wareName) {
            return ware->getCurrentValue();
        }
    }
    return -1.0; // Or throw an exception for item not found
}

const std::vector<std::shared_ptr<Ware>>& Markt::getWaren() const {
    return waren;
}

bool Markt::removeWare(std::shared_ptr<Ware> ware) {
    auto it = std::find_if(waren.begin(), waren.end(), [&](const auto& w) {
        return w->getName() == ware->getName();
    });
    if (it != waren.end()) {
        waren.erase(it);
        return true;
    }
    return false;
}

bool Markt::executeBuyOffer(std::shared_ptr<Ware> ware, NutzerKonto& buyer, int units) {
    double angebotspreis = ware->getAngebotspreis();
    double kosten = angebotspreis * units;
    if (buyer.auszahlen(kosten)) {
        // Assuming offerWare function in NutzerKonto takes name and price
        buyer.offerWare(ware->getName(), angebotspreis); // Add to buyer's inventory
        return true;
    }
    return false;
}
