#define PYBIND11_DETAILED_ERROR_MESSAGES

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/complex.h>
#include <pybind11/chrono.h>

#include <iostream> 
#include <string.h> 

#include "robot/robot.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(Kobuki, m) {
    m.doc() = R"pbdoc(
        Kobuki robot module
        -----------------------

        .. currentmodule:: Kobuki

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    py::class_<TRawGyroData>(m, "RawGyroData")
        .def(py::init<>())
        .def_readonly("x", &TRawGyroData::x)
        .def_readonly("y", &TRawGyroData::y)
        .def_readonly("z", &TRawGyroData::z);

    py::class_<TExtraRequestData>(m, "ExtraRequestData")
        .def(py::init<>())
        .def_readonly("HardwareVersionMajor", &TExtraRequestData::HardwareVersionMajor)
        .def_readonly("HardwareVersionMinor", &TExtraRequestData::HardwareVersionMinor)
        .def_readonly("HardwareVersionPatch", &TExtraRequestData::HardwareVersionPatch)
        .def_readonly("FirmwareVersionMajor", &TExtraRequestData::FirmwareVersionMajor)
        .def_readonly("FirmwareVersionMinor", &TExtraRequestData::FirmwareVersionMinor)
        .def_readonly("FirmwareVersionPatch", &TExtraRequestData::FirmwareVersionPatch)
        .def_readonly("UDID0", &TExtraRequestData::UDID0)
        .def_readonly("UDID1", &TExtraRequestData::UDID1)
        .def_readonly("UDID2", &TExtraRequestData::UDID2)
        .def_readonly("PIDtype", &TExtraRequestData::PIDtype)
        .def_readonly("PIDgainP", &TExtraRequestData::PIDgainP)
        .def_readonly("PIDgainI", &TExtraRequestData::PIDgainI)
        .def_readonly("PIDgainD", &TExtraRequestData::PIDgainD);

    py::class_<TKobukiData>(m, "KobukiData")
        .def(py::init<>())
        .def_readonly("timestamp", &TKobukiData::timestamp)
        .def_readonly("BumperLeft", &TKobukiData::BumperLeft)
        .def_readonly("BumperCenter", &TKobukiData::BumperCenter)
        .def_readonly("BumperRight", &TKobukiData::BumperRight)
        .def_readonly("CliffLeft", &TKobukiData::CliffLeft)
        .def_readonly("CliffCenter", &TKobukiData::CliffCenter)
        .def_readonly("CliffRight", &TKobukiData::CliffRight)
        .def_readonly("WheelDropLeft", &TKobukiData::WheelDropLeft)
        .def_readonly("WheelDropRight", &TKobukiData::WheelDropRight)
        .def_readonly("EncoderRight", &TKobukiData::EncoderRight)
        .def_readonly("EncoderLeft", &TKobukiData::EncoderLeft)
        .def_readonly("PWMright", &TKobukiData::PWMright)
        .def_readonly("PWMleft", &TKobukiData::PWMleft)
        .def_readonly("ButtonPress", &TKobukiData::ButtonPress)
        .def_readonly("Charger", &TKobukiData::Charger)
        .def_readonly("Battery", &TKobukiData::Battery)
        .def_readonly("overCurrent", &TKobukiData::overCurrent)
        .def_readonly("IRSensorRight", &TKobukiData::IRSensorRight)
        .def_readonly("IRSensorCenter", &TKobukiData::IRSensorCenter)
        .def_readonly("IRSensorLeft", &TKobukiData::IRSensorLeft)
        .def_readonly("GyroAngle", &TKobukiData::GyroAngle)
        .def_readonly("GyroAngleRate", &TKobukiData::GyroAngleRate)
        .def_readonly("CliffSensorRight", &TKobukiData::CliffSensorRight)
        .def_readonly("CliffSensorCenter", &TKobukiData::CliffSensorCenter)
        .def_readonly("CliffSensorLeft", &TKobukiData::CliffSensorLeft)
        .def_readonly("wheelCurrentLeft", &TKobukiData::wheelCurrentLeft)
        .def_readonly("wheelCurrentRight", &TKobukiData::wheelCurrentRight)
        .def_readonly("frameId", &TKobukiData::frameId)
        .def_readonly("gyroData", &TKobukiData::gyroData)
        .def_readonly("digitalInput", &TKobukiData::digitalInput)
        .def_readonly("analogInputCh0", &TKobukiData::analogInputCh0)
        .def_readonly("analogInputCh1", &TKobukiData::analogInputCh1)
        .def_readonly("analogInputCh2", &TKobukiData::analogInputCh2)
        .def_readonly("analogInputCh3", &TKobukiData::analogInputCh3)
        .def_readonly("extraInfo", &TKobukiData::extraInfo);

    py::class_<TKobukiCoordinates>(m, "KobukiCoordinates")
        .def(py::init<>())
        .def_readwrite("x"   , &TKobukiCoordinates::x)
        .def_readwrite("y"   , &TKobukiCoordinates::y)
        .def_readwrite("phi" , &TKobukiCoordinates::phi)
        .def_readwrite("time", &TKobukiCoordinates::time)
        .def("__repr__",
        [](const TKobukiCoordinates &c) {
            return "<Kobuki.KobukiCoordinates x = " + std::to_string(c.x) + ", y = " + std::to_string(c.y) + ", phi = " + std::to_string(c.phi) + ", time = " + std::to_string(c.time) + ">";
        }
    );


    py::class_<Robot>(m, "Robot")
        .def(py::init<std::string, int, int,std::function<int(Robot&, LaserMeasurement)>&,std::string, int , int, std::function<int(Robot&, TKobukiData)>&>(), 
                "ipaddressLaser"_a = "127.0.0.1",
                "laserportRobot"_a = 52999,
                "laserportMe"_a    = 5299,
                "lascallback"_a    = Robot::do_nothing_laser,
                "ipaddressRobot"_a = "127.0.0.1",
                "robotportRobot"_a = 53000,
                "robotportMe"_a    = 5300,
                "robcallback"_a    = Robot::do_nothing_robot)
        .def("robotStart",          &Robot::robotStart,        py::call_guard<py::gil_scoped_release>())
        .def("getLastCoordinates",  &Robot::getLastCoordinates)
        .def("getPath",             &Robot::getPath)
        .def("setTranslationSpeed", &Robot::setTranslationSpeed,
                "mmpersec"_a)
        .def("setRotationSpeed",    &Robot::setRotationSpeed,
                "radpersec"_a)
        .def("setArcSpeed",         &Robot::setArcSpeed,
                "mmpersec"_a,
                "radius"_a)
        .def("waitConnection",      &Robot::waitConnection,
                "timeout"_a        = std::chrono::seconds(60), py::call_guard<py::gil_scoped_release>());

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
