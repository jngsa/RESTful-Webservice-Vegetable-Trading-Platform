#pragma once

#include "ware.hpp"
#include <vector>
#include <string>
#include <random>

class Bank {
public:
    Bank();

    float getPrice(const std::string& name) const;
    std::vector<Ware> getStocks() const;

private:
    std::vector<Ware> stocks;
    std::default_random_engine generator;
    std::normal_distribution<float> distribution;

    float generatePrice(float currentPrice, float mu, float sigma, float dt);
};


