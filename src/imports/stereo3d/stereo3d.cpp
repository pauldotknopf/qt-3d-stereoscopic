#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmlcomponent.h>

#include "qdeclarative_stereo3dvideooutput_p.h"

QT_BEGIN_NAMESPACE

class QStereo3DDeclarativeModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QStereo3DDeclarativeModule(QObject *parent = nullptr) : QQmlExtensionPlugin(parent) { }
    void registerTypes(const char *uri) override
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Stereo3D"));
        qmlRegisterType<QDeclarativeStereo3DVideoOutput>(uri, 1, 0, "Stereo3DVideoOutput");
    }
};

QT_END_NAMESPACE

#include "stereo3d.moc"
