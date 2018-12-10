#include "qdeclarative_stereo3dvideooutput_p.h"

QDeclarativeStereo3DVideoOutput::QDeclarativeStereo3DVideoOutput(QObject *parent)
    : QObject(parent)
{

}

QDeclarativeStereo3DVideoOutput::~QDeclarativeStereo3DVideoOutput()
{
}

QAbstractVideoSurface* QDeclarativeStereo3DVideoOutput::videoSurface()
{
    return m_videoSurface;
}

void QDeclarativeStereo3DVideoOutput::setVideoSurface(QAbstractVideoSurface* videoSurface)
{
    if(videoSurface == m_videoSurface) {
        return;
    }
    m_videoSurface = videoSurface;
    if(m_videoSurface != nullptr) {
        QObject::connect(m_videoSurface, &QAbstractVideoSurface::nativeResolutionChanged, this, &QDeclarativeStereo3DVideoOutput::nativeResolutionChanged);
        QObject::connect(m_videoSurface, &QAbstractVideoSurface::surfaceFormatChanged, this, &QDeclarativeStereo3DVideoOutput::surfaceFormatChanged);
    }
    QVideoSurfaceFormat format(QSize(100,100), QVideoFrame::PixelFormat::Format_YV12);
    bool result = m_videoSurface->start(format);
    qDebug("%d",  result);
    emit videoSurfaceChanged();
}

void QDeclarativeStereo3DVideoOutput::nativeResolutionChanged(const QSize& size)
{
    qCritical("native %d x %d", size.width(), size.height());
}

void QDeclarativeStereo3DVideoOutput::surfaceFormatChanged(const QVideoSurfaceFormat &format)
{
    QSize size = format.frameSize();
    //qCritical("%d x %d", size.width(), size.height());
}
