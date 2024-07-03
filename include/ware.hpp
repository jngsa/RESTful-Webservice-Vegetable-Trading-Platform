#pragma once

#include <string>

class Ware {
private:
    std::string name;
    float price;
    int units; // Added units attribute

public:
    Ware(const std::string& name, float price, int units = 0); // Added units parameter

    std::string getName() const;
    float getPrice() const;
    int getUnits() const; // Getter for units

    void setPrice(float price);
    void addUnits(int additionalUnits);
    void removeUnits(int unitsToRemove);
};
