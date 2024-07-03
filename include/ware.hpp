#pragma once

#include <string>

class Ware {
private:
    std::string name;
    float price;
    int units; 

public:
    Ware(const std::string& name, float price, int units = 0); 

    std::string getName() const;
    float getPrice() const;
    int getUnits() const; 

    void setPrice(float price);
    void addUnits(int additionalUnits);
    void removeUnits(int unitsToRemove);
};
