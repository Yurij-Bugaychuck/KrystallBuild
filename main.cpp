#include <QApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include <QQuickStyle>
#include<mainwindow.h>


#include <QtOpenGL>
#include "glWindow/globjwin.h"
#include "glWindow/glbox.h"
#include <QAxFactory>

QAXFACTORY_BEGIN(
    "{2c3c183a-eeda-41a4-896e-3d9c12c3577d}", // type library ID
    "{83e16271-6480-45d5-aaf1-3f40b7661ae4}") // application ID
    QAXCLASS(GLBox)
QAXFACTORY_END()

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine *engine = new QQmlApplicationEngine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
     QQuickStyle::setStyle("Material");

    MainWindow W(engine);
    engine->rootContext()->setContextProperty("MainWindow", &W);
    engine->load(url);

    return app.exec();
}
