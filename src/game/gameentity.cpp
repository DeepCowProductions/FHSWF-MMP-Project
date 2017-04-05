#include "gameentity.h"

GameEntity::GameEntity(GameEngine * engine , GLBody * model)
{
    m_engine = engine;
    m_glModel = model;

    m_guiTransformation.setToIdentity();

}

GameEntity::~GameEntity()
{

}

void GameEntity::draw(GLESRenderer * renderer)
{
    if (renderer == NULL){
        qDebug() << "GameEntity::draw : renderer is null!";
        return;
    }
    m_glModel->setTransformation(renderTransformation());
    m_glModel->draw(renderer);
}

void GameEntity::snycForRendering()
{
    qDebug() << m_guiTransformation;
    qDebug() << m_renderTransformation;
    setRenderTransformation(transformation());
    qDebug() << m_guiTransformation;
    qDebug() << m_renderTransformation;
}

bool GameEntity::tryMove(QVector3D direction)
{
    translate(direction);
    return true;
}

bool GameEntity::checkCollision(GameEntity *other)
{
    if (other == NULL){
        qDebug() << "GameEntity::checkCollision : other is null! nothing to check against I guess...";
        return false;
    }
    if (getCollisionType() == CollisionType::AABB && other->getCollisionType() == CollisionType::AABB)
        return performCollDetection_AABBvsAABB(other);
    if (getCollisionType() == CollisionType::SPHERE && other->getCollisionType() == CollisionType::AABB)
        return performCollDetection_SPHEREvsAABB(other);
    if (getCollisionType() == CollisionType::AABB && other->getCollisionType() == CollisionType::SPHERE)
        return other->performCollDetection_SPHEREvsAABB(this);
    if (getCollisionType() == CollisionType::AABB && other->getCollisionType() == CollisionType::AABB)
        return performCollDetection_SPHEREvsSPHERE(other);
    qDebug() << "GameEntity::checkCollision : unable to determine collision case! returning false...";
    return false;
}

bool GameEntity::performCollDetection_AABBvsAABB(GameEntity * other)
{
    if (other == NULL)
        return false;
    //### TBI
    return false;
}

bool GameEntity::performCollDetection_SPHEREvsAABB(GameEntity * other)
{
    if (other == NULL)
        return false;
    //### TBI
    return false;
}

bool GameEntity::performCollDetection_SPHEREvsSPHERE(GameEntity * other)
{
    if (other == NULL)
        return false;
    //### currently works over radius given by glModel....
    double allowedDistance = glModel()->getRadius() + other->glModel()->getRadius();
    return (getVirtualCenter() - other->getVirtualCenter()).length() <= allowedDistance;
}

QMatrix4x4 GameEntity::transformation() const
{
    return m_guiTransformation;
}

void GameEntity::setTransformation(const QMatrix4x4 &transformation)
{
    m_guiTransformation = transformation;
//    m_virtualCenter = m_transformation.column(4).toVector3D();
}

void GameEntity::rotate(float angle, QVector3D axsis)
{
    m_guiTransformation.rotate(angle,axsis);
}

void GameEntity::translate(QVector3D direction)
{
    qDebug() << "translating entity towards" << direction;
    m_guiTransformation.translate(direction);
    qDebug() << m_guiTransformation;
    qDebug() << m_renderTransformation;
    //    m_virtualCenter += direction;
}

void GameEntity::setRotationDirection(QVector3D direction)
{
    QQuaternion q;
//    qDebug() << v_Y << direction;
    q = q.rotationTo(v_Y,direction);
//    qDebug() << q;
    QVector3D l = getVirtualCenter();
//    qDebug() << m_transformation;
    m_guiTransformation.setToIdentity();
//    qDebug() << m_transformation;
    m_guiTransformation.rotate(q);
//    qDebug() << m_transformation;
    setVirtualCenter(l);
//    qDebug() << m_transformation;
}

QVector3D GameEntity::getVirtualCenter() const
{
    return m_guiTransformation.column(3).toVector3D();
}

void GameEntity::setVirtualCenter(const QVector3D v)
{
    m_guiTransformation.setColumn(3,QVector4D(v,(m_guiTransformation(3,3))));
}

GLBody* GameEntity::glModel()
{
    return m_glModel;
}

bool GameEntity::operator ==(const GameEntity &other)
{
    return (/*m_direction == other.direction() && m_velocity == other.velocity() && */m_guiTransformation == other.transformation());
//    return (this == &other);
}

bool GameEntity::operator !=(const GameEntity &other)
{
    return !(*this == other);
}

GameEngine *GameEntity::engine() const
{
    return m_engine;
}

CollisionType GameEntity::getCollisionType() const
{
    return m_collisionType;
}

void GameEntity::setCollisionType(const CollisionType &collisionType)
{
    m_collisionType = collisionType;
}

void GameEntity::setRenderTransformation(const QMatrix4x4 &renderTransformation)
{
    m_renderTransformation = renderTransformation;
}

QMatrix4x4 GameEntity::renderTransformation() const
{
    return m_renderTransformation;
}

