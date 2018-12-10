#ifndef QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H
#define QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H

#include <QtQml/qqml.h>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>

class QDeclarativeStereo3DVideoOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface NOTIFY videoSurfaceChanged)

public:
    QDeclarativeStereo3DVideoOutput(QObject *parent = nullptr);
    ~QDeclarativeStereo3DVideoOutput();

    QAbstractVideoSurface* videoSurface();
    void setVideoSurface(QAbstractVideoSurface* videoSurface);

signals:
    void videoSurfaceChanged();

private:
    QAbstractVideoSurface* m_videoSurface;

private slots:
    void nativeResolutionChanged(const QSize& size);
    void surfaceFormatChanged(const QVideoSurfaceFormat &format);
};

#endif // QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H
