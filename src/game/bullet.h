#ifndef BULLET_H
#define BULLET_H

#include "../globjects/glbullet.h"
#include "gameentity.h"

class Bullet : public GameEntity
{
public:
    Bullet(GameEngine * engine, GLBullet * model);
    Bullet(GameEngine * engine, GLBullet * model, double v, QVector3D direction, QVector3D location);
//    ~Bullet();

    double velocity() const;
    void setVelocity(double velocity);

    QVector3D direction() const;
    void setDirection(const QVector3D &direction);

private:

    QVector3D m_direction;
    double m_velocity;

};

#endif // BULLET_H
