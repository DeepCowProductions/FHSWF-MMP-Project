#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../globjects/glspaceship.h"
#include "gameentity.h"
#include "singleshottimer.h"
#include <QTimer>

/**
 * @brief The Spaceship class is the class for the players spaceship.
 *  Holds 3 additional BoundingBoxes for collision detection and therefore overwrites some of the collisionDetection functions.
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class Spaceship : public GameEntity, public SingleShotTimer
{
public:
    Spaceship(GameEngine * engine,GLSpaceShip * model);
    ~Spaceship();

    virtual bool performCollDetection_AABBvsAABB(GameEntity *other);
    virtual bool performCollDetection_AABBvsSPHERE(GameEntity *other);

private:

    //### collisionboxes
    TAABB * m_subBoundingBox1;
    TAABB * m_subBoundingBox2;
    TAABB * m_subBoundingBox3;
};

#endif // SPACESHIP_H
