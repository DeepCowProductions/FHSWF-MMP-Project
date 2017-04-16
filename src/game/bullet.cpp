#include "bullet.h"

Bullet::Bullet(GameEngine *engine, GLBullet * model) : GameEntity(engine, model)
{

    m_direction = QVector3D(0.0,0.0,0.0);
    m_velocity = 0.0;
    setCollisionType(CollisionType::AABB);
}

Bullet::Bullet(GameEngine *engine, GLBullet *model, double v, QVector3D direction, QVector3D location, TAABB *bb) : GameEntity(engine,model)
{
    m_direction = direction;
    m_velocity = v;
    setCollisionType(CollisionType::AABB);;
    setVirtualCenter(location);
    setBoundingBox(bb) ;
}


double Bullet::velocity() const
{
    return m_velocity;
}

void Bullet::setVelocity(double velocity)
{
    m_velocity = velocity;
}

QVector3D Bullet::direction() const
{
    return m_direction;
}

void Bullet::setDirection(const QVector3D &direction)
{
    m_direction = direction;
}


