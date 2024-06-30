#pragma once

#include <vector>
#include <memory>
#include "ware.hpp"

class Markt {
private:
    std::vector<std::shared_ptr<Ware>> waren;

public:
    Markt(); // Constructor declaration

    void addWare(std::shared_ptr<Ware> ware);
    const std::vector<std::shared_ptr<Ware>>& getWaren() const;
};


