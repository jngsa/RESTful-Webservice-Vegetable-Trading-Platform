#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "ware.hpp"

class NutzerKonto {
private:
    double guthaben;
    std::vector<std::shared_ptr<Ware>> inventar;

public:
    NutzerKonto(double startGuthaben); // Constructor declaration

    double getGuthaben() const;
    const std::vector<std::shared_ptr<Ware>>& getInventar() const;

    void kaufeWare(std::shared_ptr<Ware> ware);
    void verkaufeWare(std::shared_ptr<Ware> ware);
};

