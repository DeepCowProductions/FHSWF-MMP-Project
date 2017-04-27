#ifndef SINGLESHOTTIMER_H
#define SINGLESHOTTIMER_H


/**
 * @brief The SingleShotTimer class is a class for the shoot timer,
 * in which we say when the entity can shoot.
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class SingleShotTimer
{
public:
    SingleShotTimer();

    int getCooldown() const;
    void setCooldown(int ticks);

    bool isReadyToShoot() const;

    int getCurrentCooldownTick() const;
    void setCurrentCooldownTick(int currentCooldownTick);

    /**
     * @brief shoot calls cooldown timer.
     */
    void shoot();

    void doCooldownTick();

private:
    int m_cooldown;
    int m_currentCooldownTick = 0;

};

#endif // SINGLESHOTTIMER_H
