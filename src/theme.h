
#ifndef THEME_H
#define THEME_H


#include <QObject>


class Theme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isLight READ isLight WRITE setIsLight NOTIFY isLightChanged)
public:
    explicit Theme(QObject *parent = nullptr);
    bool isLight();

signals:
    void isLightChanged();

public slots:
    void setIsLight(bool);

private:
    bool m_isLight;
};

#endif // THEME_H
