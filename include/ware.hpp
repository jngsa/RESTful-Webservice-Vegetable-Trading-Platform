#pragma once

#include <string>

class Ware {
private:
    std::string name;
    double aktuellerWert;
    double angebotspreis;

public:
    Ware(const std::string& name, double startWert);
    std::string getName() const;
    double getCurrentValue() const;
    double getAngebotspreis() const;
    void setAngebotspreis(double angebotspreis);
    void updatePreis();
};
