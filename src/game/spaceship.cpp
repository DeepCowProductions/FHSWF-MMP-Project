#include "spaceship.h"
#include "gameengine.h"

Spaceship::Spaceship(GameEngine *engine, GLSpaceShip * model) : GameEntity(engine, model)
{
    m_cooldonwTimer.setSingleShot(true);
//    m_cooldonwTimer.connect(&m_cooldonwTimer, &QTimer::timeout, &m_cooldonwTimer, &QTimer::stop);
    setWeaponCooldown(400);
}

int Spaceship::getWeaponCooldown() const
{
    return m_cooldonwTimer.interval();
}

void Spaceship::setWeaponCooldown(int msec)
{
    m_cooldonwTimer.setInterval(msec);
}

bool Spaceship::isReadyToShoot() const
{
    return !(m_cooldonwTimer.isActive());
}

void Spaceship::shoot()
{
    qDebug() << "shooting with ship occoured";
    m_cooldonwTimer.start();
}
