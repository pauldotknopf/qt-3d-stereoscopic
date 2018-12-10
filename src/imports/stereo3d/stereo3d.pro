QT += qml stereo3d stereo3d-private multimedia-private

load(qml_plugin)

OTHER_FILES += \
    plugin.json qmldir

SOURCES += \
    stereo3d.cpp \
    qdeclarative_stereo3dvideooutput_p.cpp

HEADERS += \
    qdeclarative_stereo3dvideooutput_p.h
