#include <pybind11/pybind11.h>

namespace py = pybind11;

enum MarkerType { chessboard, tag };


class MarkerDetector {
    public:
    MarkerDetector() { }
    struct Params {
        int rows;
        int cols;
        static Params create(MarkerType markerType) {
            static Params markerTypes[] = {
                    { 1, 2 },
                    { 3, 4 }
            };
            return markerTypes[markerType];
        }
    };

};


PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example"; // optional module docstring

    py::enum_<MarkerType>(m, "MarkerType")
         .value("chessboard", MarkerType::chessboard)
         .value("tag",        MarkerType::tag)
         .export_values();

    py::class_<MarkerDetector>(m, "MarkerDetector")
            .def(py::init<>());

    py::class_<MarkerDetector::Params>(m, "MarkerDetectorParams")
            .def(py::init<>())
            .def_readwrite("rows", &MarkerDetector::Params::rows)
            .def_readwrite("cols", &MarkerDetector::Params::cols)
            .def("create", (MarkerDetector::Params (*)(MarkerType)) &MarkerDetector::Params::create);
}
