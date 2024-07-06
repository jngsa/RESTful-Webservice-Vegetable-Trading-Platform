#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <bank.hpp>
#include <ware.hpp>

namespace py = pybind11;

PYBIND11_MODULE(bank, m) {
    py::class_<Bank>(m, "Bank")
        .def(py::init<>())
        .def("getPrice", &Bank::getPrice, py::arg("name"))
        .def("getStocks", &Bank::getStocks);
}