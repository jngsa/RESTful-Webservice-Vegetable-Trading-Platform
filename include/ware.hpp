#pragma once

#include <string>

class Ware {
public:
    Ware(const std::string& name, float price, int units);

    std::string getName() const;
    float getPrice() const;
    int getUnits() const;

    void setPrice(float price);
    void addUnits(int additionalUnits);
    void removeUnits(int unitsToRemove);

private:
    std::string name;
    float price;
    int units;
};

