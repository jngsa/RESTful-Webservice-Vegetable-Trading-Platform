#pragma once

#include <string>
#include <vector>
#include "ware.hpp"

class Konto {
private:
    std::string benutzername;
    float guthaben;
    std::vector<Ware> inventar;
    std::vector<Ware> offers;
    int nextOfferID;

public:
    Konto(const std::string& benutzername);

    float getGuthaben() const;
    std::vector<Ware> getInventar() const;
    std::vector<Ware> getOffers() const;
    int getNextOfferID() const;

    void einzahlen(float betrag);
    bool auszahlen(float betrag);
    void offerWare(const std::string& name, float price, int units);
    bool buyWare(int offerID, float& totalPrice);
    void addUnits(const std::string& name, int units);
    void removeUnits(const std::string& name, int units);
    Ware* findWare(const std::string& name);
};

