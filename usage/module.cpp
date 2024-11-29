#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "bsp_tree2d.cpp"

namespace py = pybind11;

PYBIND11_MODULE(bsp_tree_module, m) {
    py::class_<Node>(m, "Node");

    py::class_<BSPTree>(m, "BSPTree")
        .def(py::init<const std::vector<Line>&>())
        .def("consult_intersection", &BSPTree::consult_intersection);
}
