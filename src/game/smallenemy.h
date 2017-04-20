#ifndef SMALLENEMY_H
#define SMALLENEMY_H

#include "gameentity.h"
#include "singleshottimer.h"

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
