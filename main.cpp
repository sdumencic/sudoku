
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "grid.h"
#include "player.h"
#include "theme.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    grid g;
    Player p;
    Theme t;

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/sudoku/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("grid", &g);
    engine.rootContext()->setContextProperty("player", &p);
    engine.rootContext()->setContextProperty("theme", &t);

    engine.load(url);

    app.setWindowIcon(QIcon("./images/sudoku.png"));

    return app.exec();
}
