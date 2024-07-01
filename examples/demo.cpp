#include <iostream>
#include "konto.hpp"
#include "ware.hpp"
#include "markt.hpp"

int main() {
    // Create a Konto (Account) object for a user
    Konto konto("Max Mustermann");

    // Display initial account balance
    std::cout << "Initial Guthaben: " << konto.getGuthaben() << std::endl;

    // Display initial inventory
    std::cout << "Initial Inventar:" << std::endl;
    std::vector<Ware> inventar = konto.getInventar();
    for (const auto& ware : inventar) {
        std::cout << "- " << ware.getName() << " (Units: " << ware.getUnits() << ")" << std::endl;
    }

    // Offer a ware for sale
    std::cout << std::endl << "Angebot:" << std::endl;
    konto.offerWare("Sonnenblumenöl", 15.0f, 5);

    // Display current offers
    std::vector<Ware> offers = konto.getOffers();
    for (const auto& offer : offers) {
        std::cout << "- " << offer.getName() << " (Price: " << offer.getPrice() << ", Units: " << offer.getUnits() << ")" << std::endl;
    }

    // Simulate buying a ware from the market
    Markt markt;
    std::vector<Ware> stocks = markt.getStocks();

    std::cout << std::endl << "Markt (Stock Prices):" << std::endl;
    for (const auto& stock : stocks) {
        std::cout << "- " << stock.getName() << " (Price: " << stock.getPrice() << ", Units: " << stock.getUnits() << ")" << std::endl;
    }

    // Update stock prices
    std::cout << std::endl << "Markt nach Preisupdate:" << std::endl;
    markt.updatePrices();
    stocks = markt.getStocks();
    for (const auto& stock : stocks) {
        std::cout << "- " << stock.getName() << " (Price: " << stock.getPrice() << ", Units: " << stock.getUnits() << ")" << std::endl;
    }

    // Simulate depositing and withdrawing money
    konto.einzahlen(500.0f);
    std::cout << std::endl << "Guthaben nach Einzahlung: " << konto.getGuthaben() << std::endl;

    bool success = konto.auszahlen(200.0f);
    if (success) {
        std::cout << "Auszahlung erfolgreich. Neues Guthaben: " << konto.getGuthaben() << std::endl;
    } else {
        std::cout << "Auszahlung nicht möglich wegen unzureichendem Guthaben." << std::endl;
    }

    return 0;
}
