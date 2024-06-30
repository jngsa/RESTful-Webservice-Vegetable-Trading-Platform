// Nutzer.hpp

#pragma once

#include <string>

struct Nutzer {
    int NutzerID;
    std::string Benutzername;
    std::string Passwort;

    Nutzer(int id, const std::string& benutzername, const std::string& passwort);
};
