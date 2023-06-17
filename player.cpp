
#include "player.h"
#include <QDebug>

Player::Player(QObject *parent)
    : QObject{parent}
    , m_name("Gost")
{}

QString Player::name()
{
    return m_name;
}

void Player::setName(QString newVar)
{
    if (m_name != newVar) {
        m_name = newVar;
        emit nameChanged();
    }
}
