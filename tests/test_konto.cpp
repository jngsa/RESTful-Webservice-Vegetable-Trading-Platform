#include <gtest/gtest.h>
#include "konto.hpp"
#include "bank.hpp"
#include "ware.hpp"

class KontoTest : public ::testing::Test {
protected:
    Konto konto;
    Bank bank;

    KontoTest() : konto("felix", "passwort") {}
};

TEST_F(KontoTest, GetBenutzernameundGetPasswort) {
    EXPECT_EQ(konto.getBenutzername(), "felix");
    EXPECT_EQ(konto.getPasswort(), "passwort");
}

TEST_F(KontoTest, ConstructorTest) {
    // prueft ob Konto mit 1000 Coins initialisiert wurdfe
    EXPECT_EQ(konto.getGuthaben(), 1000.0f);
    // leeres Inventar
    EXPECT_TRUE(konto.istInventarEmpty());
}

TEST_F(KontoTest, Einzahlen) {
    konto.einzahlen(500.0f);
    EXPECT_EQ(konto.getGuthaben(), 1500.0f);
}

TEST_F(KontoTest, Auszahlen) {
    EXPECT_TRUE(konto.auszahlen(500.0f));
    EXPECT_EQ(konto.getGuthaben(), 500.0f);

    // versucht, mehr Geld als Guthaben abzuheben
    EXPECT_FALSE(konto.auszahlen(1000.0f)); 
    EXPECT_EQ(konto.getGuthaben(), 500.0f); 
}

TEST_F(KontoTest, BuyWare) {
    // toleranz fuer Rundungsfehler
    const float tolerance = 1e-1;

    // 10 Einheiten von Sonnenblumenoel kaufen
    konto.buyWare(bank, "Zwiebeln", 10);
    EXPECT_NEAR(konto.getGuthaben(), 1000.0f - bank.getPrice("Zwiebeln") * 10, tolerance);
    EXPECT_FALSE(konto.istInventarEmpty());
    EXPECT_EQ(konto.getInventar().at("Zwiebeln").getUnits(), 10);

    // versucht 200 Einheiten davon zu kaufen (nur 90 Units bleiben uebrig)
    EXPECT_THROW(konto.buyWare(bank, "Zwiebeln", 200), std::invalid_argument);
    EXPECT_NEAR(konto.getGuthaben(), 1000.0f - bank.getPrice("Zwiebeln") * 10, tolerance);
    EXPECT_EQ(konto.getInventar().at("Zwiebeln").getUnits(), 10);
}

TEST_F(KontoTest, SellWare) {
    // toleranz fuer Rundungsfehler
    const float tolerance = 1e-3;

    // Kauft 10 Units und verkauft 5 davon
    konto.buyWare(bank, "Zwiebeln", 10);
    konto.sellWare(bank, "Zwiebeln", 5);
    EXPECT_NEAR(konto.getGuthaben(), 1000.0f - bank.getPrice("Zwiebeln") * 5, tolerance);
    EXPECT_EQ(konto.getInventar().at("Zwiebeln").getUnits(), 5);

    // nur 5 Units uebrig
    EXPECT_THROW(konto.sellWare(bank, "Zwiebeln", 15), std::invalid_argument);
    EXPECT_EQ(konto.getInventar().at("Zwiebeln").getUnits(), 5);

    // nicht existierende Ware verkaufen
    EXPECT_THROW(konto.sellWare(bank, "NonExistentWare", 5), std::invalid_argument);
}

