#include "markt.hpp"
#include <cmath>    
#include <iostream> 

Markt::Markt()
    : generator(std::random_device{}()), distribution(0.0f, 1.0f) {

    std::vector<std::string> funnyNames = {
        "Sonnenblumenöl", "Klausurzulassungen", "Lidl", "Aldi",
        "Penny", "Edeka", "Rewe", "Boes",
        "Netto", "Ichweissnicht"
    };

    for (const auto& name : funnyNames) {
        float startPrice = 10.0f * (2 * distribution(generator) - 1.0f);
        float tendenz = 0.3f * (2 * distribution(generator) - 1.0f);
        float streuung = 0.8f;
        float dt = 0.001f;

        float price = generatePrice(startPrice, tendenz, streuung, dt);

        stocks.push_back(Ware(name, price, 0)); // 0 units(?)
    }
}

std::vector<Ware> Markt::getStocks() const {
    return stocks;
}

void Markt::updatePrices() {
    for (auto& stock : stocks) {
        float startPrice = stock.getPrice();
        float tendenz = 0.3f * (2 * distribution(generator) - 1.0f);
        float streuung = 0.8f;
        float dt = 0.001f;

        float price = generatePrice(startPrice, tendenz, streuung, dt);

        stock.setPrice(price);
    }
}

float Markt::generatePrice(float start, float tendenz, float streuung, float dt) {
    float sqdt = std::sqrt(dt);
    float Y = 2 * distribution(generator) - 1.0f;
    return start * (1 + tendenz * dt + streuung * sqdt * Y);
}
