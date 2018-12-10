#ifndef QSTEREO3DMEDIAOBJECT_H
#define QSTEREO3DMEDIAOBJECT_H

#include <QtMultimedia/qmediaobject.h>

class QStereo3DMediaObjectPrivate;
class QStereo3DMediaObject : public QMediaObject
{
    Q_OBJECT

public:
    explicit QStereo3DMediaObject(QObject *parent = nullptr);
    ~QStereo3DMediaObject();

private:
    Q_DECLARE_PRIVATE(QStereo3DMediaObject)
};

#endif // QSTEREO3DMEDIAOBJECT_H
