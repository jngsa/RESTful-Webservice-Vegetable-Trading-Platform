#include "gtest/gtest.h"
#include "ware.hpp"
#include <stdexcept>

// constructor und getters
TEST(WareTest, ConstructorTest) {
    Ware ware("Test", 100.0, 10);
    ASSERT_EQ(ware.getName(), "Test");
    ASSERT_FLOAT_EQ(ware.getPrice(), 100.0);
    ASSERT_EQ(ware.getUnits(), 10);
}

// setPrice
TEST(WareTest, SetPriceTest) {
    Ware ware("Test", 100.0, 10);
    ware.setPrice(150.0);
    ASSERT_FLOAT_EQ(ware.getPrice(), 150.0);

    // negativer Preis
    ASSERT_THROW(ware.setPrice(-1.0), std::invalid_argument);
}

// updateUnits
TEST(WareTest, UpdateUnitsTest) {
    Ware ware("TestWare", 100.0, 10);

    // Test with positive value
    ware.updateUnits(5);
    ASSERT_EQ(ware.getUnits(), 15); // 10 + 5 = 15

    // Test with zero value
    ware.updateUnits(0);
    ASSERT_EQ(ware.getUnits(), 15); // 15 + 0 = 15

    // Test with negative value within valid range
    ware.updateUnits(-3);
    ASSERT_EQ(ware.getUnits(), 12); // 15 - 3 = 12
}


