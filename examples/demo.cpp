#include "konto.hpp"
#include <iostream>

int main() {
    // Create two accounts (Kontos)
    Konto konto1("Alice", "password1");
    Konto konto2("Bob", "password2");

    // Display initial balances
    std::cout << "Initial balances:" << std::endl;
    std::cout << "Alice's balance: " << konto1.getGuthaben() << std::endl;
    std::cout << "Bob's balance: " << konto2.getGuthaben() << std::endl;

    // Alice offers to sell 5 units of "Lidl" at a price of 15.0
    konto1.offerWare("Lidl", 15.0f, 5);

    // Display Alice's offers
    std::cout << "\nAlice's Offers:" << std::endl;
    for (size_t i = 0; i < konto1.getAllOffers().size(); ++i) {
        const Offer& offer = konto1.getAllOffers()[i];
        std::cout << "Offer " << i << ": " << offer.getUnits() << " units of " << offer.getWare().getName()
                  << " at price " << offer.getPrice() << " from " << offer.getBenutzername() << std::endl;
    }

    // Bob wants to buy 2 units of "Lidl"
    if (konto2.buyWare(0, 2)) { // Assuming Alice's offer is at index 0
        std::cout << "\nBob successfully bought 2 units of Lidl from Alice." << std::endl;
    } else {
        std::cout << "\nTransaction failed for Bob." << std::endl;
    }

    // Display updated balances
    std::cout << "\nUpdated balances:" << std::endl;
    std::cout << "Alice's balance: " << konto1.getGuthaben() << std::endl;
    std::cout << "Bob's balance: " << konto2.getGuthaben() << std::endl;

    // Display updated inventories and offers
    std::cout << "\nAlice's Inventory:" << std::endl;
    for (const auto& ware : konto1.getInventar()) {
        std::cout << "Name: " << ware.getName() << ", Units: " << ware.getUnits() << std::endl;
    }

    std::cout << "\nBob's Inventory:" << std::endl;
    for (const auto& ware : konto2.getInventar()) {
        std::cout << "Name: " << ware.getName() << ", Units: " << ware.getUnits() << std::endl;
    }

    // Display updated offers
    std::cout << "\nAlice's Updated Offers:" << std::endl;
    for (size_t i = 0; i < konto1.getAllOffers().size(); ++i) {
        const Offer& offer = konto1.getAllOffers()[i];
        std::cout << i << ": " << offer.getUnits() << " units of " << offer.getWare().getName()
                  << " at price " << offer.getPrice() << " from " << offer.getBenutzername() << std::endl;
    }

    return 0;
}
