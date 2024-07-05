#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

#include <konto.hpp>
#include <bank.hpp>
#include <ware.hpp>

namespace py = pybind11;

PYBIND11_MODULE(konto, m) {
    py::class_<Konto>(m, "Konto")
        .def(py::init<const std::string&, const std::string&>())
        .def("getBenutzername", &Konto::getBenutzername)
        .def("getPasswort", &Konto::getPasswort)
        .def("getGuthaben", &Konto::getGuthaben)
        .def("getInventar", &Konto::getInventar)
        .def("sellWare", &Konto::sellWare, py::arg("bank"), py::arg("name"), py::arg("units"))
        .def("buyWare", &Konto::buyWare, py::arg("bank"), py::arg("name"), py::arg("units"))
        .def("einzahlen", &Konto::einzahlen, py::arg("betrag"))
        .def("auszahlen", &Konto::auszahlen, py::arg("betrag"));
}

PYBIND11_MODULE(bank, m) {
    py::class_<Bank>(m, "bank")
        .def(py::init<>())
        .def("getPrice", &Bank::getStocks, py::arg("name"))
        .def("getStocks", &Bank::getStocks);
}

PYBIND11_MODULE(ware, m) {
    py::class_<Ware>(m, "Ware")
        .def(py::init<const std::string&, float, int>())
        .def("getName", &Ware::getName)
        .def("getPrice", &Ware::getPrice)
        .def("getUnits", &Ware::getUnits)
        .def("setPrice", &Ware::setPrice, py::arg("price"))
        .def("addUnits", &Ware::addUnits, py::arg("additionalUnits"))
        .def("removeUnits", &Ware::removeUnits, py::arg("unitsToRemove"));
}