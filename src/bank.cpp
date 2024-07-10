#include "bank.hpp"
#include <cmath>
#include <stdexcept>

Bank::Bank()
    : generator(std::random_device{}()), distribution(0.0f, 1.0f) {

    std::vector<std::string> funnyNames = {
        "Brokkoli", "Zwiebeln", "Knoblauch", "Lauch",
        "Blumenkohl", "Karotte", "Petersilie", "Spinat",
        "Kartoffel", "Tomate"
    };

    for (const auto& name : funnyNames) {
        float startPrice;
        do {
            startPrice = 10.0f * distribution(generator) + 10.0f; // positiver Startpreis
        } while (startPrice <= 0.0f);

        stocks.push_back(Ware(name, startPrice, 100)); 
    }
}


float Bank::getPrice(const std::string& name) const {
    for (const auto& ware : stocks) {
        if (ware.getName() == name) {
            return ware.getPrice();
        }
    }
    throw std::invalid_argument("Ware existiert nicht");
}

std::vector<Ware> Bank::getStocks() const {
    return stocks;
}

void Bank::updatePrices() {
    float mu = 0.05f; // Tendenz
    float sigma = 0.2f; // Standardabweichung
    float dt = 1.0f; 
    float sqdt = std::sqrt(dt); 

    for (auto& stock : stocks) {
        float currentPrice = stock.getPrice();
        float Yt = distribution(generator); // Zufallsvariable

        // Randomwalk
        float newPrice = currentPrice + mu * dt * currentPrice + sigma * sqdt * Yt * currentPrice;

        if (newPrice > 0.0f) {
            stock.setPrice(newPrice);
        } else {
            stock.setPrice(0.01f); 
        }
    }
}

void Bank::updateUnits(const std::string& name, const int& betrag) {
    for (auto& ware : stocks) {
        if (ware.getName() == name) {
            ware.updateUnits(betrag);
            return;
        }
    }
    throw std::invalid_argument("Ware nicht gefunden");
}
