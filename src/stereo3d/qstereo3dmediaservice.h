#ifndef QSTEREO3DMEDIASERVICE_H
#define QSTEREO3DMEDIASERVICE_H

#include <QMediaService>

class QStereo3DMediaService : public QMediaService
{
    Q_OBJECT

public:
    explicit QStereo3DMediaService(QObject* parent = nullptr);
    QMediaControl* requestControl(const char *name);
    void releaseControl(QMediaControl *control);
};

#endif // QSTEREO3DMEDIASERVICE_H
