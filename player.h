
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

class Player : public QObject
{
    //    QML_ELEMENT
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit Player(QObject *parent = nullptr);
    QString name();

signals:
    void nameChanged();

public slots:
    void setName(QString);

private:
    QString m_name;
};

#endif // PLAYER_H
