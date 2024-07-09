#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

#include <konto.hpp>
#include <ware.hpp>
#include <bank.hpp>

namespace py = pybind11;

PYBIND11_MODULE(konto, m) {
    py::register_exception<std::invalid_argument>(m, "InvalidArgument");

    py::class_<Konto>(m, "Konto")
        .def(py::init<const std::string&, const std::string&>())
        .def("getBenutzername", &Konto::getBenutzername)
        .def("getPasswort", &Konto::getPasswort)
        .def("getGuthaben", &Konto::getGuthaben)
        .def("getInventar", &Konto::getInventar)
        .def("istInventarEmpty", &Konto::istInventarEmpty)
        .def("sellWare", &Konto::sellWare, py::arg("bank"), py::arg("name"), py::arg("units"))
        .def("buyWare", &Konto::buyWare, py::arg("bank"), py::arg("name"), py::arg("units"))
        .def("einzahlen", &Konto::einzahlen, py::arg("betrag"))
        .def("auszahlen", &Konto::auszahlen, py::arg("betrag"));
}