#ifndef SINGLESHOTTIMER_H
#define SINGLESHOTTIMER_H


/**
 * @brief The SingleShotTimer class
 *  A Simple timer wich ticks down every time when countDown() is called.
 * Time is calculated in plane intgers. Timer counts down form cooldown to 0.
 * Current cooldown can be acquired by calling getCurrentCooldownTick().
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class SingleShotTimer
{
public:
    SingleShotTimer();

    /**
     * @brief getCooldown
     * getter for cooldown period.
     * @return hwo many times the timer has to count down to reach zero.
     */
    int getCooldown() const;
    /**
     * @brief setCooldown set the cooldown period. I.e. how many times it has to count down to reach zero again.
     * @param ticks ticks in integer.
     */
    void setCooldown(int ticks);

    /**
     * @brief isReadyToShoot
     * @return if the timer has cooled down to zero and is ready to be activated again.
     */
    bool isReadyToShoot() const;

    /**
     * @brief getCurrentCooldownTick
     * @return current tick
     */
    int getCurrentCooldownTick() const;
    /**
     * @brief setCurrentCooldownTick set current tick. Not supposed to be used. Timers dont usually work that way.
     * @param currentCooldownTick
     */
    void setCurrentCooldownTick(int currentCooldownTick);

    /**
     * @brief shoot calls cooldown timer.
     * activates the timer and sets currentCooldownTick to cooldown.
     */
    void shoot();

    /**
     * @brief countDown counts down currentCooldownTimer by 1. Does nothing when reached 0.
     */
    void countDown();

private:
    int m_cooldown;
    int m_currentCooldownTick = 0;

};

#endif // SINGLESHOTTIMER_H
