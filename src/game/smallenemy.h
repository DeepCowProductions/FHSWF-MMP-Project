#ifndef SMALLENEMY_H
#define SMALLENEMY_H

#include "gameentity.h"
#include "singleshottimer.h"

/**
 * @brief The SmallEnemy class a entity class for the enemy of the game.
 * laneId is currnetly unused. This class does currently not implement any new functionallity.
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class SmallEnemy : public GameEntity, public SingleShotTimer
{
public:
    SmallEnemy(GameEngine * engine, GLBody * model);

    int laneID() const;
    void setLaneID(int laneID);

private:
    int m_laneID;

};

#endif // SMALLENEMY_H
