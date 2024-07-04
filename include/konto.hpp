#pragma once

#include "ware.hpp"
#include "bank.hpp" 
#include <string>
#include <unordered_map>

class Konto {
public:
    Konto(const std::string& benutzername, const std::string& passwort);

    std::string getBenutzername() const;
    std::string getPasswort() const;
    float getGuthaben() const;
    std::unordered_map<std::string, Ware> getInventar() const;

    void sellWare(Bank& bank, const std::string& name, int units);
    void buyWare(Bank& bank, const std::string& name, int units);

    void einzahlen(float betrag);
    bool auszahlen(float betrag);

private:
    std::string benutzername;
    std::string passwort;
    float guthaben;
    std::unordered_map<std::string, Ware> inventar;

    void setGuthaben(float betrag);
};


