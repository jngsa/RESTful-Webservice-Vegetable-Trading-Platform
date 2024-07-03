#pragma once

#include "ware.hpp"
#include <vector>
#include <random>   // for std::default_random_engine, std::normal_distribution

class Markt {
private:
    std::vector<Ware> stocks;

    // Random number generation parameters
    std::default_random_engine generator;
    std::normal_distribution<float> distribution;

    // Helper method to generate price using random walk
    float generatePrice(float start, float tendenz, float streuung, float dt);

public:
    Markt();

    std::vector<Ware> getStocks() const;
    void updatePrices();
};
