#pragma once

#include <vector>
#include "ware.hpp"

class Markt {
private:
    std::vector<Ware> stocks;

public:
    Markt();

    std::vector<Ware> getStocks() const;
    void updatePrices();
};

