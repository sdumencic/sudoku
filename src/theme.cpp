
#include "theme.h"

Theme::Theme(QObject *parent)
    : QObject{parent}
    , m_isLight(true)
{

}

bool Theme::isLight()
{
    return m_isLight;
}

void Theme::setIsLight(bool newVar)
{
    if (m_isLight != newVar) {
        m_isLight = newVar;
        emit isLightChanged();
    }
}
