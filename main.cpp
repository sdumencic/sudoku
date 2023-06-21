
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "player.h"
#include "src/gametimer.h"
#include "src/grid.h"
#include "src/theme.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    grid g;
    Player p;
    Theme t;
    qmlRegisterType<GameTimer>("GameTimer", 1, 0, "GameTimer");
    qmlRegisterType<grid>("GridClass", 1, 0, "GridClass");
    qmlRegisterType<Player>("User", 1, 0, "User");
    qmlRegisterType<Theme>("Theme", 1, 0, "Theme");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/sudoku/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    //    engine.setInitialProperties({{"_user", QVariant::fromValue(&p)}});

    engine.load(url);

    app.setWindowIcon(QIcon("./images/sudoku.png"));

    return app.exec();
}
