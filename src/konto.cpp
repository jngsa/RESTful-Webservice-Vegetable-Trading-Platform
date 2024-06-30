#include "konto.hpp"
#include <algorithm> // Include algorithm header for std::find

NutzerKonto::NutzerKonto(double startGuthaben)
    : guthaben(startGuthaben) {
    // Constructor definition
}

double NutzerKonto::getGuthaben() const {
    return guthaben;
}

const std::vector<std::shared_ptr<Ware>>& NutzerKonto::getInventar() const {
    return inventar;
}

void NutzerKonto::kaufeWare(std::shared_ptr<Ware> ware) {
    if (guthaben >= ware->aktuellerWert) {
        guthaben -= ware->aktuellerWert;
        inventar.push_back(ware);
    }
}

void NutzerKonto::verkaufeWare(std::shared_ptr<Ware> ware) {
    auto it = std::find_if(inventar.begin(), inventar.end(),
                           [&](const auto& w) { return w == ware; });
    if (it != inventar.end()) {
        guthaben += (*it)->aktuellerWert;
        inventar.erase(it);
    }
}
