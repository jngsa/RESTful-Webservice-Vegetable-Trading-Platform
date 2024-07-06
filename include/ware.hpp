#pragma once

#include <string>

class Ware {
public:
    Ware(const std::string& name, float price, int units);

    std::string getName() const;
    float getPrice() const;
    int getUnits() const;

    void setPrice(float price);
    void updateUnits(int anzahl);

private:
    std::string name;
    float price;
    int units;
};

