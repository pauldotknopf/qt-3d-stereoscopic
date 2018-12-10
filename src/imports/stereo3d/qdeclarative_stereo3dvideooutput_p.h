#ifndef QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H
#define QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H

#include <QtQml/qqml.h>
#include <QPointer>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QScopedPointer>
#include <QMediaObject>
#include <private/qdeclarativevideooutput_backend_p.h>

class QDeclarativeStereo3DVideoOutput;
class QDeclarativeStereo3DVideoSurface : public QAbstractVideoSurface
{
public:
    QDeclarativeStereo3DVideoSurface(QDeclarativeStereo3DVideoOutput* control, bool isLeft);
    virtual ~QDeclarativeStereo3DVideoSurface();

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool present(const QVideoFrame &frame);

private:
    QDeclarativeStereo3DVideoOutput* m_control;
    bool m_isLeft;
};

class QDeclarativeStereo3DVideoOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface NOTIFY videoSurfaceChanged)
    Q_PROPERTY(QObject* leftSource READ leftSource WRITE setLeftSource NOTIFY leftSourceChanged)
    Q_PROPERTY(QObject* rightSource READ rightSource WRITE setRightSource NOTIFY rightSourceChanged)

public:
    QDeclarativeStereo3DVideoOutput(QObject *parent = nullptr);
    ~QDeclarativeStereo3DVideoOutput();

    QAbstractVideoSurface* videoSurface();
    void setVideoSurface(QAbstractVideoSurface* videoSurface);

    QObject* leftSource();
    void setLeftSource(QObject* leftSource);

    QObject* rightSource();
    void setRightSource(QObject* rightSource);

signals:
    void videoSurfaceChanged();
    void leftSourceChanged();
    void rightSourceChanged();

private:
    QAbstractVideoSurface* m_videoSurface;

    QPointer<QObject> m_leftSource;
    QPointer<QDeclarativeStereo3DVideoSurface> m_leftSurface;
    QPointer<QMediaObject> m_leftMediaObject;
    QPointer<QMediaService> m_leftMediaService;

    QPointer<QObject> m_rightSource;
    QPointer<QDeclarativeStereo3DVideoSurface> m_rightSurface;
    QPointer<QMediaObject> m_rightMediaObject;
    QPointer<QMediaService> m_rightMediaService;

    QScopedPointer<QDeclarativeVideoBackend> m_backend;

private slots:
    void nativeResolutionChanged(const QSize& size);
    void surfaceFormatChanged(const QVideoSurfaceFormat &format);
    void _q_updateLeftMediaObject();
    void _q_updateRightMediaObject();

private:
    bool _q_presentLeftFrame(const QVideoFrame& frame);
    bool _q_presentRightFrame(const QVideoFrame& frame);

    friend class QDeclarativeStereo3DVideoSurface;
};

#endif // QDECLARATIVE_STEREO3DVIDEOOUTPUT_P_H
