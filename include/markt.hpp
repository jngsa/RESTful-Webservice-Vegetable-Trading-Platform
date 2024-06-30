// markt.hpp


#include "ware.hpp" // Include necessary headers
#include "konto.hpp"
#include <vector>
#include <memory>

class Markt {
public:
    Markt(); // Constructor

    void addWare(std::shared_ptr<Ware> ware);
    void updatePreise();
    double getCurrentPrice(const std::string& wareName) const;
    const std::vector<std::shared_ptr<Ware>>& getWaren() const;
    bool removeWare(std::shared_ptr<Ware> ware);
    bool executeBuyOffer(std::shared_ptr<Ware> ware, NutzerKonto& buyer, int units);

private:
    std::vector<std::shared_ptr<Ware>> waren;
};

