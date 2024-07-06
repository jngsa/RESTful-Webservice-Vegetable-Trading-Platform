#include "bank.hpp"
#include <cmath>
#include <stdexcept>

Bank::Bank()
    : generator(std::random_device{}()), distribution(0.0f, 1.0f) {

    std::vector<std::string> funnyNames = {
        "Sonnenblumenöl", "Klausurzulassungen", "Lidl", "Aldi",
        "Penny", "Edeka", "Rewe", "Boes",
        "Netto", "Ichweissnicht"
    };

    for (const auto& name : funnyNames) {
        float startPrice;
        do {
            startPrice = 10.0f * distribution(generator) + 10.0f; // Generate a new start price
        } while (startPrice <= 0.0f); // Repeat until startPrice is positive

        float mu = 0.05f; // Assume 5% drift
        float sigma = 0.2f; // Assume 20% volatility
        float dt = 1.0f; // One time step

        float price = generatePrice(startPrice, mu, sigma, dt);

        stocks.push_back(Ware(name, price, 100));
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

float Bank::generatePrice(float currentPrice, float mu, float sigma, float dt) {
    // Generate a normally distributed random variable
    float Yt = distribution(generator);

    // Log-normal price update
    float logPrice = std::log(currentPrice);
    float newLogPrice = logPrice + (mu - 0.5f * sigma * sigma) * dt + sigma * std::sqrt(dt) * Yt;

    // Exponentiate to get the new price
    return std::exp(newLogPrice);
}

void Bank::updateUnits(const std::string& name, const int& betrag) {
    for (auto& ware : stocks) {
        if (ware.getName() == name) {
            ware.updateUnits(betrag);
        }
        else {
            throw std::invalid_argument("Ware nicht gefunden");
        }
    }
}
