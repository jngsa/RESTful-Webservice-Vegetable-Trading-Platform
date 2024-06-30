#include "markt.hpp"

void Markt::wareKaufen(int nutzerID, int warenID, int menge, double gesamtpreis) {
    auto& nutzerKonto = nutzerkonten[nutzerID];
    nutzerKonto.setGuthaben(nutzerKonto.getGuthaben() - gesamtpreis);

    auto& ware = waren[warenID];
    ware.setAnzahl(ware.getAnzahl() + menge);
}

void Markt::wareVerkaufen(int nutzerID, int warenID, int menge, double angebotspreis) {
    auto& nutzerKonto = nutzerkonten[nutzerID];
    nutzerKonto.setGuthaben(nutzerKonto.getGuthaben() + angebotspreis * menge);

    auto& ware = waren[warenID];
    ware.setAnzahl(ware.getAnzahl() - menge);
}

void Markt::aktualisiereHandelswerte(double inflationsrate, double wechselkurs, double zinssatz) {
    for (auto& [id, ware] : waren) {
        double updatedValue = ware.getAktuellerWert() * (1 + inflationsrate);
        ware.setAktuellerWert(updatedValue);
    }
}
