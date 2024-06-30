#pragma once

#include <string>

class Ware {
public:
    std::string name;
    double aktuellerWert;

    Ware(const std::string& name, double aktuellerWert); // Constructor declaration

    std::string getName() const; // Method to get the name of the ware
    double getPreis() const;     // Method to get the price of the ware
};
