#pragma once


#include "ware.hpp"
#include <vector>
#include <memory>

class NutzerKonto {
private:
    double guthaben;
    std::vector<std::shared_ptr<Ware>> inventar;

public:
    NutzerKonto(double startGuthaben);
    double getGuthaben() const;
    const std::vector<std::shared_ptr<Ware>>& getInventar() const;
    void einzahlen(double betrag);
    bool auszahlen(double betrag);
    void offerWare(const std::string& wareName, double angebotspreis);
    bool buyWare(const std::string& wareName, double angebotspreis, int units);
};
