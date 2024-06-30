#include <iostream>
#include <memory>
#include "konto.hpp"

// Function to display the inventory of a user
void displayInventory(const std::vector<std::shared_ptr<Ware>>& inventar) {
    for (const auto& item : inventar) {
        std::cout << "  " << item->getName() << " (Preis: " << item->getPreis() << ")" << std::endl;
    }
}

int main() {
    // Create some items (Waren)
    auto item1 = std::make_shared<Ware>("Item1", 100); // Example item with name and price
    auto item2 = std::make_shared<Ware>("Item2", 50);

    // Create NutzerKonto objects
    NutzerKonto konto1(500); // Initial balance of 500
    NutzerKonto konto2(300); // Initial balance of 300

    // Simulate transactions
    konto1.kaufeWare(item1); // User1 buys Item1
    konto2.kaufeWare(item2); // User2 buys Item2

    // Simulate selling items
    konto1.verkaufeWare(item1); // User1 sells Item1

    // Display final state
    std::cout << "Konto1: Guthaben = " << konto1.getGuthaben() << std::endl;
    std::cout << "  Inventar:" << std::endl;
    displayInventory(konto1.getInventar());

    std::cout << "Konto2: Guthaben = " << konto2.getGuthaben() << std::endl;
    std::cout << "  Inventar:" << std::endl;
    displayInventory(konto2.getInventar());

    return 0;
}
