#include <iostream>
#include "ware.hpp"
#include "bank.hpp"
#include "konto.hpp"

int main() {
    // Create a bank with some initial stocks
    Bank bank;
    std::vector<Ware> stocks = bank.getStocks();

    // Display the initial stocks in the bank
    std::cout << "Initial stocks in the bank:" << std::endl;
    for (const auto& ware : stocks) {
        std::cout << "Name: " << ware.getName() << ", Price: " << ware.getPrice() << ", Units: " << ware.getUnits() << std::endl;
    }

    // Create an account
    Konto account("username", "password");

    // Buy some units of a ware from the bank
    std::string wareToBuy = "Lidl";
    int unitsToBuy = 10;

    try {
        account.buyWare(bank, wareToBuy, unitsToBuy);
        std::cout << "Successfully bought " << unitsToBuy << " units of " << wareToBuy << " from the bank." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Failed to buy ware: " << e.what() << std::endl;
    }

    // Display updated guthaben and inventory in the account
    std::cout << "Current guthaben in the account: " << account.getGuthaben() << std::endl;

    std::cout << "Current inventory in the account:" << std::endl;
    auto inventory = account.getInventar();
    for (const auto& item : inventory) {
        std::cout << "Name: " << item.second.getName() << ", Units: " << item.second.getUnits() << std::endl;
    }

    // Sell some units of a ware to the bank
    std::string wareToSell = "Lidl";
    int unitsToSell = 5;

    try {
        account.sellWare(bank, wareToSell, unitsToSell);
        std::cout << "Successfully sold " << unitsToSell << " units of " << wareToSell << " to the bank." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Failed to sell ware: " << e.what() << std::endl;
    }

    // Display updated guthaben and inventory in the account
    std::cout << "Updated guthaben in the account: " << account.getGuthaben() << std::endl;

    std::cout << "Updated inventory in the account:" << std::endl;
    inventory = account.getInventar();
    for (const auto& item : inventory) {
        std::cout << "Name: " << item.second.getName() << ", Units: " << item.second.getUnits() << std::endl;
    }

    return 0;
}
