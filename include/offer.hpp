#pragma once

#include "ware.hpp"
#include <string>

class Offer {
private:
    std::string benutzername; 
    Ware ware;
    float price;
    int units;

public:
    Offer(const std::string& benutzername, const Ware& ware, float price, int units);

    std::string getBenutzername() const;
    Ware getWare() const;
    float getPrice() const;
    int getUnits() const;

    void setUnits(int units);
};

