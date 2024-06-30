#include "markt.hpp"

Markt::Markt() {
    // Constructor definition
}

void Markt::addWare(std::shared_ptr<Ware> ware) {
    waren.push_back(ware);
}

const std::vector<std::shared_ptr<Ware>>& Markt::getWaren() const {
    return waren;
}
