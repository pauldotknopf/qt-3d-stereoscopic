#include "qstereo3dmediaservice.h"

QStereo3DMediaService::QStereo3DMediaService(QObject* parent)
    : QMediaService(parent)
{

}

QMediaControl* QStereo3DMediaService::requestControl(const char *name)
{
    qCritical("%s", name);
    return nullptr;
}

void QStereo3DMediaService::releaseControl(QMediaControl *control)
{
    Q_UNUSED(control);
}
