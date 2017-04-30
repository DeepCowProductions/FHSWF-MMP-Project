#include "spaceship.h"
#include "gameengine.h"

Spaceship::Spaceship(GameEngine *engine, GLSpaceShip * model) : GameEntity(engine, model)
{
    //backplane
    //middlestrip
    //front       boundings
    m_subBoundingBox1 = new TAABB(QVector3D(3.5,0.7,-4.0), QVector3D(-3.5,0.0,-7.0));
    m_subBoundingBox2 = new TAABB(QVector3D(1.2,1.0,3.5), QVector3D(-1.2,-0.2,-6.5));
    m_subBoundingBox3 = new TAABB(QVector3D(2.5,0.9,2.5), QVector3D(-2.5,0.30,-1.0));

    setCollisionType(CollisionType::AABB);
    setCooldown(Spaceinvaders::playerShootingCooldownInGameTicks);
}

Spaceship::~Spaceship()
{
//    if (m_subBoundingBox1)
//        delete m_subBoundingBox1;
//    if (m_subBoundingBox2)
//        delete m_subBoundingBox2;
//    if (m_subBoundingBox3)
//        delete m_subBoundingBox3;

}


bool Spaceship::performCollDetection_AABBvsAABB(GameEntity *other)
{
    if (performCollDetection_SPHEREvsSPHERE(other)){
        QVector3D b1max = m_subBoundingBox1->max + getVirtualCenter();
        QVector3D b1min = m_subBoundingBox1->min + getVirtualCenter();
        QVector3D b2max = m_subBoundingBox2->max + getVirtualCenter();
        QVector3D b2min = m_subBoundingBox2->min + getVirtualCenter();
        QVector3D b3max = m_subBoundingBox3->max + getVirtualCenter();
        QVector3D b3min = m_subBoundingBox3->min + getVirtualCenter();
        QVector3D b0max = other->getBoundingBox()->max + other->getVirtualCenter();
        QVector3D b0min = other->getBoundingBox()->min + other->getVirtualCenter();

        qDebug() << b1max << b1min;
        qDebug() << b0max << b0min;
        int a =(( b1max.x() > b0min.x() && b1min.x() < b0max.x() && b1max.y() > b0min.y() &&
                  b1min.y() < b0max.y() && b1max.z() > b0min.z() && b1min.z() < b0max.z()     )  ||
                ( b2max.x() > b0min.x() && b2min.x() < b0max.x() && b2max.y() > b0min.y() &&
                  b2min.y() < b0max.y() && b2max.z() > b0min.z() && b2min.z() < b0max.z()     )  ||
                ( b3max.x() > b0min.x() && b3min.x() < b0max.x() && b3max.y() > b0min.y() &&
                  b3min.y() < b0max.y() && b3max.z() > b0min.z() && b3min.z() < b0max.z()     )
               );
        qDebug() << "AABB AABB coll res:  " << a;
        return a;

    }
    return false;
}

bool Spaceship::performCollDetection_AABBvsSPHERE(GameEntity *other)
{
    if (performCollDetection_SPHEREvsSPHERE(other)){
        QVector3D b1max = m_subBoundingBox1->max + getVirtualCenter();
        QVector3D b1min = m_subBoundingBox1->min + getVirtualCenter();
        QVector3D b2max = m_subBoundingBox2->max + getVirtualCenter();
        QVector3D b2min = m_subBoundingBox2->min + getVirtualCenter();
        QVector3D b3max = m_subBoundingBox3->max + getVirtualCenter();
        QVector3D b3min = m_subBoundingBox3->min + getVirtualCenter();

        float r2 = other->glModel()->getRadius() * other->glModel()->getRadius();
        float dmin1 = 0;
        float dmin2 = 0;
        float dmin3 = 0;
        for(int i = 0; i < 3; i++ ) {
          if( other->getVirtualCenter()[i] < b1min[i] )        dmin1 += Spaceinvaders::sqr( other->getVirtualCenter()[i] - b1min[i] );
          else if( other->getVirtualCenter()[i] > b1max[i] )   dmin1 += Spaceinvaders::sqr( other->getVirtualCenter()[i] - b1max[i] );
          if( other->getVirtualCenter()[i] < b2min[i] )        dmin2 += Spaceinvaders::sqr( other->getVirtualCenter()[i] - b2min[i] );
          else if( other->getVirtualCenter()[i] > b2max[i] )   dmin2 += Spaceinvaders::sqr( other->getVirtualCenter()[i] - b2max[i] );
          if( other->getVirtualCenter()[i] < b3min[i] )        dmin3 += Spaceinvaders::sqr( other->getVirtualCenter()[i] - b3min[i] );
          else if( other->getVirtualCenter()[i] > b3max[i] )   dmin3 += Spaceinvaders::sqr( other->getVirtualCenter()[i] - b3max[i] );
        }
        if( dmin1 <= r2)
            return true;
        else if( dmin2 <= r2)
            return true;
        else if( dmin3 <= r2)
            return true;
        else
            return false;
    }
    return false;
}
