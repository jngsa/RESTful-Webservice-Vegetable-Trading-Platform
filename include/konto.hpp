#pragma once
#include <string>

class NutzerKonto {
private:
    std::string benutzername;
    std::string passwort;
    double guthaben = 0.0;

public:
    // Constructor
    NutzerKonto(const std::string& benutzername = "", const std::string& passwort = "");

    // Getters
    const std::string& getBenutzername() const;
    const std::string& getPasswort() const;
    double getGuthaben() const;

    // Setter
    void setGuthaben(double newGuthaben);
};




