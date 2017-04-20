#include "gameentity.h"

GameEntity::GameEntity(GameEngine * engine , GLBody * model)
{
    m_engine = engine;
    m_glModel = model;
    m_collisionType = CollisionType::SPHERE;

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
//    qDebug() << m_guiTransformation;
//    qDebug() << m_renderTransformation;
    setRenderTransformation(transformation());
//    qDebug() << m_guiTransformation;
//    qDebug() << m_renderTransformation;
}

bool GameEntity::tryMove(QVector3D direction)
{
    QVector3D d = getVirtualCenter() + direction;
    if ( d.x() < Spaceinvaders::playFieldBounds  && d.x() > -Spaceinvaders::playFieldBounds )
        translate(direction);
    return true;
}

bool GameEntity::checkCollision(GameEntity *other)
{
    if (other == NULL){
        qDebug() << "GameEntity::checkCollision : other is null! nothing to check against I guess... returning false";
        return false;
    }
    if (this == other){
        qDebug() << "GameEntity::checkCollision : other is equal to this! nothing to check against I guess... returning true";
        return true;
    }

    if (getCollisionType() == CollisionType::AABB && other->getCollisionType() == CollisionType::AABB)
        return performCollDetection_AABBvsAABB(other);
    if (getCollisionType() == CollisionType::SPHERE && other->getCollisionType() == CollisionType::AABB)
        return performCollDetection_SPHEREvsAABB(other);
    if (getCollisionType() == CollisionType::AABB && other->getCollisionType() == CollisionType::SPHERE)
        return performCollDetection_AABBvsSPHERE(other);
    if (getCollisionType() == CollisionType::AABB && other->getCollisionType() == CollisionType::AABB)
        return performCollDetection_SPHEREvsSPHERE(other);
    qDebug() << "GameEntity::checkCollision : unable to determine collision case! returning false...";
    return false;
}

bool GameEntity::performCollDetection_AABBvsAABB(GameEntity * other)
{   
    // apply current transformation to boundingBox by moving box with virtualCenter
    QVector3D b1max = getBoundingBox()->max + getVirtualCenter();
    QVector3D b1min = getBoundingBox()->min + getVirtualCenter();
    QVector3D b2max = other->getBoundingBox()->max + other->getVirtualCenter();
    QVector3D b2min = other->getBoundingBox()->min + other->getVirtualCenter();
    //Check if Box1's max is greater than Box2's min and Box1's min is less than Box2's max
    return (
                b1max.x() > b2min.x() &&
                b1min.x() < b2max.x() &&
                b1max.y() > b2min.y() &&
                b1min.y() < b2max.y() &&
                b1max.z() > b2min.z() &&
                b1min.z() < b2max.z()    );
    //If not, it will return false
}

bool GameEntity::performCollDetection_SPHEREvsAABB(GameEntity * other)
{
    // apply tranformation to bounderyBox by moving box with virtualCenter
    QVector3D b2max = other->getBoundingBox()->max + other->getVirtualCenter();
    QVector3D b2min = other->getBoundingBox()->min + other->getVirtualCenter();
    // slower step by step implementaion:
//    QVector3D halfExtend = (b2max - b2min) * 0.5;
//    QVector3D boxCenter = b2min + halfExtend;
//    QVector3D d = getVirtualCenter() - boxCenter;
//    //    halfExtend = halfExtend.abs(); ?
//    QVector3D clamped(SpaceinvaderUtils::clamp(d.x(), -halfExtend.x(), halfExtend.x()),
//             SpaceinvaderUtils::clamp(d.y(), -halfExtend.y(), halfExtend.y()),
//             SpaceinvaderUtils::clamp(d.z(), -halfExtend.z(), halfExtend.z()));
//    QVector3D closest = aabb_center + clamped;
//    // Retrieve vector between center circle and closest point AABB and check if length <= radius
//    d = closest - center;
//    return d.length() < glModel()->getRadius();

    // faster:
    float r2 = glModel()->getRadius() * glModel()->getRadius();
    float dmin = 0;
    for(int i = 0; i < 3; i++ ) {
      if( getVirtualCenter()[i] < b2min[i] )        dmin += Spaceinvaders::sqr( getVirtualCenter()[i] - b2min[i] );
      else if( getVirtualCenter()[i] > b2max[i] )   dmin += Spaceinvaders::sqr( getVirtualCenter()[i] - b2max[i] );
    }
    return dmin <= r2;
}

bool GameEntity::performCollDetection_AABBvsSPHERE(GameEntity *other)
{
    QVector3D b2max = getBoundingBox()->max + getVirtualCenter();
    QVector3D b2min = getBoundingBox()->min + getVirtualCenter();

    float r2 = other->glModel()->getRadius() * other->glModel()->getRadius();
    float dmin = 0;
    for(int i = 0; i < 3; i++ ) {
      if( other->getVirtualCenter()[i] < b2min[i] )        dmin += Spaceinvaders::sqr( other->getVirtualCenter()[i] - b2min[i] );
      else if( other->getVirtualCenter()[i] > b2max[i] )   dmin += Spaceinvaders::sqr( other->getVirtualCenter()[i] - b2max[i] );
    }
    return dmin <= r2;
}

bool GameEntity::performCollDetection_SPHEREvsSPHERE(GameEntity * other)
{
    //### currently works over radius given by glModel and center from transformation matirx
    return (getVirtualCenter() - other->getVirtualCenter()).length() <= glModel()->getRadius() + other->glModel()->getRadius();
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
//    qDebug() << "translating entity towards" << direction;
    m_guiTransformation.translate(direction);
//    qDebug() << m_guiTransformation;
//    qDebug() << m_renderTransformation;
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
    return (m_guiTransformation == other.transformation());
//    return (/*m_direction == other.direction() && m_velocity == other.velocity() && */m_guiTransformation == other.transformation());
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

TAABB *GameEntity::getBoundingBox() const
{
    return m_boundingBox;
}

void GameEntity::setBoundingBox(TAABB *boundingBox)
{
    m_boundingBox = boundingBox;
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
