#include <iostream>
#include <string>
#include "ware.hpp"
#include "konto.hpp"
#include "bank.hpp"

int main() {
    // Create a Bank object
    Bank bank;

    // Print initial stock information
    std::cout << "Initial Bank Stocks:" << std::endl;
    for (const auto& ware : bank.getStocks()) {
        std::cout << ware.getName() << ": " << ware.getUnits() << " units, "
                  << ware.getPrice() << " price" << std::endl;
    }
    std::cout << std::endl;

    // Create a Konto object
    Konto konto("Benutzer", "Passwort");

    // Try buying 10 units of "Sonnenblumenöl"
    try {
        std::cout << "Buying 10 units of Sonnenblumenöl..." << std::endl;
        konto.buyWare(bank, "Sonnenblumenoel", 10);
        std::cout << "Buy successful!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Print updated stock information
    std::cout << "Updated Bank Stocks after buying:" << std::endl;
    for (const auto& ware : bank.getStocks()) {
        std::cout << ware.getName() << ": " << ware.getUnits() << " units, "
                  << ware.getPrice() << " price" << std::endl;
    }
    std::cout << std::endl;

    // Print Konto's inventory
    std::cout << "Konto's inventory after buying:" << std::endl;
    for (const auto& [name, ware] : konto.getInventar()) {
        std::cout << name << ": " << ware.getUnits() << " units, "
                  << ware.getPrice() << " price" << std::endl;
    }
    std::cout << std::endl;

    // Try selling 5 units of "Sonnenblumenöl"
    try {
        std::cout << "Selling 5 units of Sonnenblumenöl..." << std::endl;
        konto.sellWare(bank, "Sonnenblumenoel", 5);
        std::cout << "Sell successful!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Print updated stock information
    std::cout << "Updated Bank Stocks after selling:" << std::endl;
    for (const auto& ware : bank.getStocks()) {
        std::cout << ware.getName() << ": " << ware.getUnits() << " units, "
                  << ware.getPrice() << " price" << std::endl;
    }
    std::cout << std::endl;

    // Print Konto's inventory
    std::cout << "Konto's inventory after selling:" << std::endl;
    for (const auto& [name, ware] : konto.getInventar()) {
        std::cout << name << ": " << ware.getUnits() << " units, "
                  << ware.getPrice() << " price" << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
