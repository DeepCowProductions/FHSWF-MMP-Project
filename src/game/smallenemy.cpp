#include "smallenemy.h"

SmallEnemy::SmallEnemy(GameEngine *engine, GLBody *model) : GameEntity(engine, model)
{
    setCooldown(Spaceinvaders::enemyShootingCooldownInGameTicks);
    setBoundingBox(new TAABB(glModel()->getMaxCoordinate(),glModel()->getMinCoordinate()));
    setCollisionType(CollisionType::AABB);
}

int SmallEnemy::laneID() const
{
    return m_laneID;
}

void SmallEnemy::setLaneID(int laneID)
{
    m_laneID = laneID;
}
