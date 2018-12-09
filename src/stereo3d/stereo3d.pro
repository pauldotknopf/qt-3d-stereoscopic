TARGET = Stereo3D
QT -= core gui

HEADERS += \
    modtest.h \
    modtestprivate_p.h \
    stereo3dglobal.h

SOURCES += \
    modtest.cpp \
    modtestprivate_p.cpp

load(qt_module)

# This is needed if you have no tests (tests/).
# CONFIG -= create_cmake
