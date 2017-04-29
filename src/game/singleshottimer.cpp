#include "singleshottimer.h"

SingleShotTimer::SingleShotTimer()
{

}

int SingleShotTimer::getCooldown() const
{
    return m_cooldown;
}

void SingleShotTimer::setCooldown(int ticks)
{
    m_cooldown = ticks;
}

bool SingleShotTimer::isReadyToShoot() const
{
    return m_currentCooldownTick <= 0;
}

void SingleShotTimer::shoot()
{
    setCurrentCooldownTick(getCooldown());
}

int SingleShotTimer::getCurrentCooldownTick() const
{
    return m_currentCooldownTick;
}

void SingleShotTimer::setCurrentCooldownTick(int currentCooldownTick)
{
    m_currentCooldownTick = currentCooldownTick;
}

void SingleShotTimer::countDown()
{
    if (getCurrentCooldownTick() > 0)
        setCurrentCooldownTick(getCurrentCooldownTick() - 1);
}

