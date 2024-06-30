// Ware.hpp

#pragma once

#include <string>
#include <ctime>

struct Ware {
    int WarenID;
    std::string Name;
    double AktuellerWert;
    std::time_t LetzteAktualisierung;

    Ware(int id, const std::string& name, double aktuellerWert);
};
