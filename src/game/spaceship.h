#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../globjects/glspaceship.h"
#include "gameentity.h"
#include "singleshottimer.h"
#include <QTimer>

class Spaceship : public GameEntity, public SingleShotTimer
{
public:
    Spaceship(GameEngine * engine,GLSpaceShip * model);
    ~Spaceship();

    virtual bool performCollDetection_AABBvsAABB(GameEntity *other);
    virtual bool performCollDetection_AABBvsSPHERE(GameEntity *other);

private:

    TAABB * m_subBoundingBox1;
    TAABB * m_subBoundingBox2;
    TAABB * m_subBoundingBox3;
};

#endif // SPACESHIP_H
