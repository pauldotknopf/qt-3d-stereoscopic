#include "qstereo3dmediaobject.h"

#include <private/qmediaobject_p.h>
#include <private/qmediaserviceprovider_p.h>

class QStereo3DMediaObjectPrivate : public QMediaObjectPrivate
{
    Q_DECLARE_NON_CONST_PUBLIC(QStereo3DMediaObject)

public:
    QStereo3DMediaObjectPrivate() {}
    bool test;
};

QStereo3DMediaObject::QStereo3DMediaObject(QObject *parent)
    : QMediaObject(*new QStereo3DMediaObjectPrivate,
                 parent,
                 QMediaServiceProvider::defaultServiceProvider()->requestService(Q_MEDIASERVICE_AUDIODECODER))
{

}

QStereo3DMediaObject::~QStereo3DMediaObject()
{

}
