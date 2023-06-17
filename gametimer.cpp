
#include "gametimer.h"
#include <QTimer>
#include <chrono>
#include <iostream>

GameTimer::GameTimer(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    seconds = 0;

    connect(timer, &QTimer::timeout, this, &GameTimer::updateTimer);
}

void GameTimer::start()
{
    timer->start(1000); // 1 second interval
}

void GameTimer::stop()
{
    timer->stop();
}

void GameTimer::updateTimer()
{
    seconds++;
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;
    QString time = QString("%1:%2")
                       .arg(minutes, 2, 10, QLatin1Char('0'))
                       .arg(remainingSeconds, 2, 10, QLatin1Char('0'));
    emit timeChanged(time);
}
