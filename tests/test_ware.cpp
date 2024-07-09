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

// // addUnits
// TEST(WareTest, AddUnitsTest) {
//     Ware ware("Test", 100.0, 10);
//     ware.addUnits(5);
//     ASSERT_EQ(ware.getUnits(), 15);

//     // negative Anzahl
//     ASSERT_THROW(ware.addUnits(-1), std::invalid_argument);
// }

// // removeUnits
// TEST(WareTest, RemoveUnitsTest) {
//     Ware ware("Test", 100.0, 10);
//     ware.removeUnits(3);
//     ASSERT_EQ(ware.getUnits(), 7);

//     // negative Anzahl
//     ASSERT_THROW(ware.removeUnits(-1), std::invalid_argument);

//     // nicht genug Einheiten im Inventar
//     ASSERT_THROW(ware.removeUnits(20), std::invalid_argument);
// }


