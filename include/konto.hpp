#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "ware.hpp"
#include "offer.hpp"

class Konto {
public:
    Konto(const std::string& benutzername, const std::string& passwort);

    static Konto* getKonto(const std::string& benutzername);

    std::string getBenutzername() const;
    std::string getPasswort() const;
    float getGuthaben() const;
    std::vector<Ware> getInventar() const;
    std::vector<Offer>& getAllOffers();

    void offerWare(const std::string& name, float price, int units);
    bool buyWare(size_t offerIndex, int units);

    void addUnits(const std::string& name, int units);
    void removeUnits(const std::string& name, int units);

private:
    std::string benutzername;
    std::string passwort;
    float guthaben;
    std::vector<Ware> inventar;
    static std::vector<Offer> offers; // Static member variable declaration

    static std::unordered_map<std::string, Konto*> konten;

    Ware* findWare(const std::string& name);
    void validateOffer(const Ware& ware, int units);
    void einzahlen(float betrag);
    bool auszahlen(float betrag);
    void setGuthaben(float betrag);
};
