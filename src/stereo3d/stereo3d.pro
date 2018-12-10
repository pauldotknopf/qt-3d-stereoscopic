TARGET = Stereo3D
QT += multimedia multimedia-private

HEADERS += \
    modtest.h \
    modtestprivate_p.h \
    stereo3dglobal.h \
    qstereo3dmediaobject.h \
    qstereo3dmediaservice.h

SOURCES += \
    modtest.cpp \
    modtestprivate_p.cpp \
    qstereo3dmediaobject.cpp \
    qstereo3dmediaservice.cpp

load(qt_module)

# This is needed if you have no tests (tests/).
# CONFIG -= create_cmake
