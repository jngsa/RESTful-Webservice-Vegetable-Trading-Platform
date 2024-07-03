#pragma once

#include "ware.hpp"
#include <vector>
#include <random>   

class Markt {
private:
    std::vector<Ware> stocks;

    // fuer Random Walk
    std::default_random_engine generator;
    std::normal_distribution<float> distribution;
    float generatePrice(float start, float tendenz, float streuung, float dt);

public:
    Markt();

    std::vector<Ware> getStocks() const;
    void updatePrices();
};
