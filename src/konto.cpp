#include "konto.hpp"

NutzerKonto::NutzerKonto(const std::string& benutzername, const std::string& passwort)
    : benutzername(benutzername), passwort(passwort) {
}

const std::string& NutzerKonto::getBenutzername() const {
    return benutzername;
}

const std::string& NutzerKonto::getPasswort() const {
    return passwort;
}

double NutzerKonto::getGuthaben() const {
    return guthaben;
}

void NutzerKonto::setGuthaben(double newGuthaben) {
    guthaben = newGuthaben;
}
