
#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QDateTime>
#include <QObject>
#include <QTimer>

class GameTimer : public QObject
{
    Q_OBJECT

public:
    explicit GameTimer(QObject *parent = nullptr);

signals:
    void timeChanged(QString time);

public slots:
    void start();
    void stop();
    void reset();
    void updateTimer();
    void resume();

private:
    QTimer *timer;
    int seconds;
};

#endif // GAMETIMER_H
