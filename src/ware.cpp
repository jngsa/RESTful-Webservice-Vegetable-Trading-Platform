#include "ware.hpp"
#include <random>

Ware::Ware(const std::string& name, double startWert)
    : name(name), aktuellerWert(startWert), angebotspreis(0.0) {
    // Constructor definition
}

std::string Ware::getName() const {
    return name;
}

double Ware::getCurrentValue() const {
    return aktuellerWert;
}

double Ware::getAngebotspreis() const {
    return angebotspreis;
}

void Ware::setAngebotspreis(double angebotspreis) {
    this->angebotspreis = angebotspreis;
}

void Ware::updatePreis() {
    static std::default_random_engine generator;
    static std::normal_distribution<double> distribution(0.0, 0.5);
    double drift = distribution(generator);

    aktuellerWert *= (1 + drift);
}
