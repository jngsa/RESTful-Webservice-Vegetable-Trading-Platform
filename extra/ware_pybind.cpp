#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

#include <ware.hpp>

namespace py = pybind11;

PYBIND11_MODULE(ware, m) {
    py::class_<Ware>(m, "Ware")
        .def(py::init<const std::string&, float, int>())
        .def("getName", &Ware::getName)
        .def("getPrice", &Ware::getPrice)
        .def("getUnits", &Ware::getUnits)
        .def("setPrice", &Ware::setPrice, py::arg("price"))
        .def("updateUnits", &Ware::updateUnits, py::arg("anzahl"));
}