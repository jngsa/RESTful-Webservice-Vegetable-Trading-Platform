#include "konto.hpp"
#include "markt.hpp"
#include <iostream>

void printInventory(const NutzerKonto& konto) {
    std::cout << "Current Inventory:\n";
    const auto& inventar = konto.getInventar();
    for (const auto& ware : inventar) {
        std::cout << "- " << ware->getName() << ": " << ware->getAngebotspreis() << " (Current Price: " << ware->getCurrentValue() << ")\n";
    }
    std::cout << "Guthaben: " << konto.getGuthaben() << " coins\n";
    std::cout << "-------------------------\n";
}

int main() {
    // Create a market
    Markt markt;

    // Create a user account with initial balance
    NutzerKonto userAccount(1000.0);

    // Display initial market prices
    markt.updatePreise();
    markt.executeBuyOffer(markt.getWaren()[0], userAccount, 5); // Example transaction

    // Display initial user inventory
    printInventory(userAccount);

    // Simulate offering stock for sale
    userAccount.offerWare("Stock1", 60.0);

    // Display updated user inventory after offering
    printInventory(userAccount);

    // Simulate buying from the market
    markt.executeBuyOffer(markt.getWaren()[0], userAccount, 3);

    // Display updated user inventory after buying
    printInventory(userAccount);

    return 0;
}
