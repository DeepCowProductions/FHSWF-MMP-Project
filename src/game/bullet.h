#ifndef BULLET_H
#define BULLET_H

#include "../globjects/glbullet.h"
#include "gameentity.h"

/**
 * @brief The Bullet class
 * This class is for generating bullets, of Player and Enemy
 */
class Bullet : public GameEntity
{
public:
    Bullet(GameEngine * engine, GLBullet * model);
    Bullet(GameEngine * engine, GLBullet * model, double v, QVector3D direction, QVector3D location,TAABB * bb);
//    ~Bullet();

    /**
     * @brief velocity
     * @return the velocity of the bullet
     */
    double velocity() const;

    /**
     * @brief setVelocity sets a new velocity of the bullet
     * @param velocity for the new velocity of the bullet
     */
    void setVelocity(double velocity);

    /**
     * @brief direction
     * @return the direction of the bullet
     */
    QVector3D direction() const;

    /**
     * @brief setDirection sets a new direction of the bullet
     * @param direction is the new direction, which want to set
     */
    void setDirection(const QVector3D &direction);

private:

    QVector3D m_direction;
    double m_velocity;
};

#endif // BULLET_H
