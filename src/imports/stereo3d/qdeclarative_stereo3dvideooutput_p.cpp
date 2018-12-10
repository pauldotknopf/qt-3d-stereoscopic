#include "qdeclarative_stereo3dvideooutput_p.h"

#include <QMediaObject>
#include <QMediaService>
#include <QVideoRendererControl>

QDeclarativeStereo3DVideoSurface::QDeclarativeStereo3DVideoSurface(
        QDeclarativeStereo3DVideoOutput* control,
        bool isLeft)
    : QAbstractVideoSurface(control)
    , m_control(control)
    , m_isLeft(isLeft)
{
}

QDeclarativeStereo3DVideoSurface::~QDeclarativeStereo3DVideoSurface()
{
}

QList<QVideoFrame::PixelFormat> QDeclarativeStereo3DVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType);
    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB565;
}

bool QDeclarativeStereo3DVideoSurface::present(const QVideoFrame& frame)
{
    if (m_isLeft) {
        return m_control->_q_presentLeftFrame(frame);
    }
    return m_control->_q_presentRightFrame(frame);
}

bool QDeclarativeStereo3DVideoSurface::start(const QVideoSurfaceFormat& format)
{
    bool result = QAbstractVideoSurface::start(format);
    if(result) {
        if (m_isLeft) {
            m_control->_q_leftSurfaceStart(format);
        } else {
            m_control->_q_rightSurfaceStart(format);
        }
    }
    return result;
}

void QDeclarativeStereo3DVideoSurface::stop()
{
    QAbstractVideoSurface::stop();
    if (m_isLeft) {
        m_control->_q_leftSurfaceStop();
    } else {
        m_control->_q_rightSurfaceStop();
    }
}

QDeclarativeStereo3DVideoOutput::QDeclarativeStereo3DVideoOutput(QObject *parent)
    : QObject(parent)
    , m_videoSurface(nullptr)
    , m_leftSource(nullptr)
    , m_leftSurface(new QDeclarativeStereo3DVideoSurface(this, true))
    , m_rightSource(nullptr)
    , m_rightSurface(new QDeclarativeStereo3DVideoSurface(this, false))
{

}

QDeclarativeStereo3DVideoOutput::~QDeclarativeStereo3DVideoOutput()
{
    m_leftSource.clear();
    m_rightSource.clear();
    _q_updateLeftMediaObject();
    _q_updateRightMediaObject();
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
    emit videoSurfaceChanged();
}

QObject* QDeclarativeStereo3DVideoOutput::leftSource()
{
    return m_leftSource;
}

void QDeclarativeStereo3DVideoOutput::setLeftSource(QObject* leftSource)
{
    if (leftSource == m_leftSource.data()) {
        return;
    }

    if (m_leftSource) {
        disconnect(m_leftSource.data(), nullptr, this, SLOT(_q_updateLeftMediaObject()));
    }

    m_leftSource = leftSource;

    if (m_leftSource) {
        const QMetaObject *metaObject = m_leftSource.data()->metaObject();
        int mediaObjectPropertyIndex = metaObject->indexOfProperty("mediaObject");

        if(mediaObjectPropertyIndex == -1) {
            qWarning("no mediaObject property on leftSource");
            m_leftSource.clear();
            return;
        }

        const QMetaProperty mediaObjectProperty = metaObject->property(mediaObjectPropertyIndex);

        if(mediaObjectProperty.hasNotifySignal()) {
            QMetaMethod method = mediaObjectProperty.notifySignal();
            QMetaObject::connect(m_leftSource.data(), method.methodIndex(),
                                 this, this->metaObject()->indexOfSlot("_q_updateLeftMediaObject()"),
                                 Qt::DirectConnection, nullptr);
        }
    }

    _q_updateLeftMediaObject();
    emit leftSourceChanged();
}

QObject* QDeclarativeStereo3DVideoOutput::rightSource()
{
    return m_rightSource;
}

void QDeclarativeStereo3DVideoOutput::setRightSource(QObject* rightSource)
{
    if (rightSource == m_rightSource.data()) {
        return;
    }

    if (m_rightSource) {
        disconnect(m_rightSource.data(), nullptr, this, SLOT(_q_updateRightMediaObject()));
    }

    m_rightSource = rightSource;

    if (m_rightSource) {
        const QMetaObject *metaObject = m_rightSource.data()->metaObject();
        int mediaObjectPropertyIndex = metaObject->indexOfProperty("mediaObject");

        if(mediaObjectPropertyIndex == -1) {
            qWarning("no mediaObject property on leftSource");
            m_rightSource.clear();
            return;
        }

        const QMetaProperty mediaObjectProperty = metaObject->property(mediaObjectPropertyIndex);

        if(mediaObjectProperty.hasNotifySignal()) {
            QMetaMethod method = mediaObjectProperty.notifySignal();
            QMetaObject::connect(m_rightSource.data(), method.methodIndex(),
                                 this, this->metaObject()->indexOfSlot("_q_updateLeftMediaObject()"),
                                 Qt::DirectConnection, nullptr);
        }
    }

    _q_updateRightMediaObject();
    emit rightSourceChanged();
}

void QDeclarativeStereo3DVideoOutput::nativeResolutionChanged(const QSize& size)
{
    qCritical("native %d x %d", size.width(), size.height());
}

void QDeclarativeStereo3DVideoOutput::surfaceFormatChanged(const QVideoSurfaceFormat &format)
{
    QSize size = format.frameSize();
    qCritical("%d x %d", size.width(), size.height());
}

void QDeclarativeStereo3DVideoOutput::_q_updateLeftMediaObject()
{
    QMediaObject *mediaObject = nullptr;

    if (m_leftSource)
        mediaObject = qobject_cast<QMediaObject*>(m_leftSource.data()->property("mediaObject").value<QObject*>());

    if (m_leftMediaObject.data() == mediaObject)
        return;

    if (mediaObject) {
        if (QMediaService *service = mediaObject->service()) {
            QVideoRendererControl* renderControl = service->requestControl<QVideoRendererControl*>();
            if (renderControl) {
                renderControl->setSurface(m_leftSurface);
                m_leftMediaObject = mediaObject;
                m_leftMediaService = service;
            }
        }
    }
}

void QDeclarativeStereo3DVideoOutput::_q_updateRightMediaObject()
{
    QMediaObject *mediaObject = nullptr;

    if (m_rightSource)
        mediaObject = qobject_cast<QMediaObject*>(m_rightSource.data()->property("mediaObject").value<QObject*>());

    if (m_rightMediaObject.data() == mediaObject)
        return;

    if (mediaObject) {
        if (QMediaService *service = mediaObject->service()) {
            QVideoRendererControl* renderControl = service->requestControl<QVideoRendererControl*>();
            if (renderControl) {
                renderControl->setSurface(m_rightSurface);
                m_rightMediaObject = mediaObject;
                m_rightMediaService = service;
            }
        }
    }
}

void QDeclarativeStereo3DVideoOutput::_q_updateVideoSurfaceFormat()
{
    if (!m_leftSurfaceFormat.isValid() || !m_rightSurfaceFormat.isValid()) {
        m_videoSurface->stop();
        return;
    }
    // TODO: Check if they are the same.
    m_videoSurface->start(m_leftSurfaceFormat);
}

void QDeclarativeStereo3DVideoOutput::_q_leftSurfaceStart(const QVideoSurfaceFormat& format)
{
    m_leftSurfaceFormat = format;
    _q_updateVideoSurfaceFormat();
}

bool QDeclarativeStereo3DVideoOutput::_q_presentLeftFrame(const QVideoFrame& frame)
{
    if(m_videoSurface->isActive()) {
        return m_videoSurface->present(frame);
    }
    return false;
}

void QDeclarativeStereo3DVideoOutput::_q_leftSurfaceStop()
{
    m_leftSurfaceFormat = QVideoSurfaceFormat();
    _q_updateVideoSurfaceFormat();
}

void QDeclarativeStereo3DVideoOutput::_q_rightSurfaceStart(const QVideoSurfaceFormat& format)
{
    m_rightSurfaceFormat = format;
    _q_updateVideoSurfaceFormat();
}

bool QDeclarativeStereo3DVideoOutput::_q_presentRightFrame(const QVideoFrame& frame)
{
    if(m_videoSurface->isActive()) {
        return m_videoSurface->present(frame);
    }
    return false;
}

void QDeclarativeStereo3DVideoOutput::_q_rightSurfaceStop()
{
    m_rightSurfaceFormat = QVideoSurfaceFormat();
    _q_updateVideoSurfaceFormat();
}
