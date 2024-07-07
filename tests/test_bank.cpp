#include "gtest/gtest.h"
#include "bank.hpp"

// Test suite fuer test fixture
class BankTest : public ::testing::Test {
protected:
    Bank bank;

    void SetUp() override {
        bank = Bank();  
    }
};

// constructor
TEST_F(BankTest, ConstructorTest) {
    auto stocks = bank.getStocks();
    ASSERT_FALSE(stocks.empty()) << "Stocks sollte nicht leer sein";
    ASSERT_EQ(stocks.size(), 10) << "Es sollte 10 Waren geben";
}

// getPrice
TEST_F(BankTest, GetPriceTest) {
    auto stocks = bank.getStocks();
    std::string stockName = stocks[0].getName();
    float expectedPrice = stocks[0].getPrice();
    float price = bank.getPrice(stockName);
    ASSERT_FLOAT_EQ(price, expectedPrice) << "Preise sollen uebereinstimmen";
    // Ware existiert nicht
    ASSERT_THROW(bank.getPrice("blablabla"), std::invalid_argument)
    << "getPrice throws std::invalid_argument";
}

// updateUnits
TEST_F(BankTest, UpdateUnits) {
    
    auto stocks = bank.getStocks();    
    std::string stockName = stocks[0].getName();
    int initialUnits = stocks[0].getUnits();
    
    // positive Anzahl
    {
        SCOPED_TRACE("Um 5 Einheiten erhoehen");
        bank.updateUnits(stockName, 5);
        int updatedUnits = bank.getStocks()[0].getUnits();
        ASSERT_EQ(updatedUnits, initialUnits + 5) << "Anzahl sollte um 5 erhoeht werden";
    }
    
    initialUnits = bank.getStocks()[0].getUnits();
    
    // negative Anzahl
    {
        SCOPED_TRACE("3 Einheiten abziehen");
        bank.updateUnits(stockName, -3);
        int updatedUnits = bank.getStocks()[0].getUnits();
        ASSERT_EQ(updatedUnits, initialUnits - 3) << "3 Einheiten sollten abgezogen werden";
    }

    // nicht existierende Ware
    {
        SCOPED_TRACE("Invalide Ware");
        ASSERT_THROW(bank.updateUnits("blablabla", 5), std::invalid_argument)
            << "updateUnits should throw std::invalid_argument";
    }
}