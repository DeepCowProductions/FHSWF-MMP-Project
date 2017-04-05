#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../globjects/glspaceship.h"
#include "gameentity.h"
#include <QTimer>

class Spaceship : public GameEntity
{
public:
    Spaceship(GameEngine * engine,GLSpaceShip * model);
//    ~Spaceship();

    int getWeaponCooldown() const;
    void setWeaponCooldown(int msec);
    bool isReadyToShoot() const;

    /**
     * @brief shoot only calls cooldown timer.
     */
    void shoot();

private:
    //### cooldown between shots in milli seconds
    QTimer m_cooldonwTimer;
};

#endif // SPACESHIP_H
