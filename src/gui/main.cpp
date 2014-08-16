#include "qml/MainWindowUi.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QUrl>

QUrl adjustUrl(const QString& path)
{
#ifdef QRC_LOCAL_FILES
    return QUrl::fromLocalFile(QString("../src/gui/%1").arg(path));
#else
    return QUrl(QString("qrc:///%1").arg(path));
#endif
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(adjustUrl("qml/MainWindow.qml"));
    Q_ASSERT(engine.rootObjects().size() > 0);
    QObject* childQML = engine.rootObjects().at(0);
    Q_ASSERT(childQML);
    MainWindowUi mainWindowUi;
    mainWindowUi.setRootObject(childQML);

    return app.exec();
}
