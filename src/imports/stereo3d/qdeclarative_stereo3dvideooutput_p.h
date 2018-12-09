#ifndef QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H
#define QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H

#include <QtQml/qqml.h>

class QDeclarativeStereo3DVideoOutput : public QObject
{
    Q_OBJECT
public:
    QDeclarativeStereo3DVideoOutput(QObject *parent = nullptr);
    ~QDeclarativeStereo3DVideoOutput();
};

#endif // QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H
