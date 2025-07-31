#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "bollinger.h"

namespace py = pybind11;

PYBIND11_MODULE(bollinger_bindings, m) {
    m.def("sma", &sma, "Simple Moving Average",
          py::arg("prices"), py::arg("window"));

    m.def("std_dev", &std_dev, "Standard Deviation",
          py::arg("prices"), py::arg("window"));

    m.def("bollinger_bands", &bollinger_bands, "Compute Bollinger Bands",
          py::arg("prices"), py::arg("window"), py::arg("num_std_dev"),
          py::arg("smaa"), py::arg("upper_band"), py::arg("lower_band"), py::arg("signal"));
}