TARGET = example1
QT += quick
CONFIG += c++11

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/stereo3d/example1
INSTALLS += target
