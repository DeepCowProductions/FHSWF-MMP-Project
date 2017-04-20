#include "smallenemy.h"

SmallEnemy::SmallEnemy(GameEngine *engine, GLBody *model) : GameEntity(engine, model)
{
    setCooldown(Spaceinvaders::enemyShootingCooldownInGameTicks);
}

int SmallEnemy::laneID() const
{
    return m_laneID;
}

void SmallEnemy::setLaneID(int laneID)
{
    m_laneID = laneID;
}
