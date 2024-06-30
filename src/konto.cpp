#include "konto.hpp"

NutzerKonto::NutzerKonto(double startGuthaben)
    : guthaben(startGuthaben) {
    // Initialize with 10 units of each stock
    inventar.push_back(std::make_shared<Ware>("Stock1", 50.0));
    inventar.push_back(std::make_shared<Ware>("Stock2", 20.0));
    inventar.push_back(std::make_shared<Ware>("Stock3", 200.0));
    inventar.push_back(std::make_shared<Ware>("Stock4", 1000.0));
    inventar.push_back(std::make_shared<Ware>("Stock5", 150.0));
    inventar.push_back(std::make_shared<Ware>("Stock6", 500.0));
    inventar.push_back(std::make_shared<Ware>("Stock7", 300.0));
    inventar.push_back(std::make_shared<Ware>("Stock8", 800.0));
    inventar.push_back(std::make_shared<Ware>("Stock9", 700.0));
    inventar.push_back(std::make_shared<Ware>("Stock10", 900.0));
}

double NutzerKonto::getGuthaben() const {
    return guthaben;
}

const std::vector<std::shared_ptr<Ware>>& NutzerKonto::getInventar() const {
    return inventar;
}

void NutzerKonto::einzahlen(double betrag) {
    guthaben += betrag;
}

bool NutzerKonto::auszahlen(double betrag) {
    if (guthaben >= betrag) {
        guthaben -= betrag;
        return true;
    }
    return false;
}

void NutzerKonto::offerWare(const std::string& wareName, double angebotspreis) {
    for (auto& ware : inventar) {
        if (ware->getName() == wareName) {
            ware->setAngebotspreis(angebotspreis);
            return;
        }
    }
}

bool NutzerKonto::buyWare(const std::string& wareName, double angebotspreis, int units) {
    double kosten = angebotspreis * units;
    if (guthaben >= kosten) {
        guthaben -= kosten;
        for (auto& ware : inventar) {
            if (ware->getName() == wareName) {
                ware->updatePreis(); // Update price before adding units
                ware->setAngebotspreis(angebotspreis); // Update offered price
                return true;
            }
        }
    }
    return false;
}
