#ifndef QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H
#define QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H

#include <QtQml/qqml.h>
#include <QPointer>

#include <Stereo3D/QStereo3DMediaObject>

class QDeclarativeStereo3DVideoOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *mediaObject READ mediaObject NOTIFY mediaObjectChanged SCRIPTABLE false DESIGNABLE false)

public:
    QDeclarativeStereo3DVideoOutput(QObject *parent = nullptr);
    ~QDeclarativeStereo3DVideoOutput();

    QObject *mediaObject() { return nullptr; }

signals:
    void mediaObjectChanged();

private:
    QPointer<QMediaObject> m_mediaObject;
};

#endif // QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H
