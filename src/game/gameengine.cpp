#include "gameengine.h"

GameEngine::GameEngine(QObject *parent) : QObject(parent)
{
    //### init glObjects
    m_glbulletgreen = new GLBullet("green bullet",3.0,0.5,GLColorRgba::clGreen,"");
    m_glbulletred = new GLBullet("red bullet",3.0,0.5,GLColorRgba::clRed,"");
    m_glsphere = new GLSphere("placeHolder",3.0);
    m_glsppaceship = new GLSpaceShip("3D Spaceship / PlayersShip");
    m_glsppaceship->setTextureFile(":/spaceshipTex"); // use alias

    // init starting Entities
    m_playership = new Spaceship(this, m_glsppaceship);

    //    connect(this, &QObject::destroyed, this, &MyObject::onObjectDestroyed);

}

GameEngine::~GameEngine()
{
    m_bulletContainer.clear();

    if (m_glbulletgreen)
        delete m_glbulletgreen;
    if (m_glbulletred)
        delete m_glbulletred;

}

void GameEngine::drawEntities(GLESRenderer *renderer)
{
    for (Bullet e : m_bulletContainer){
//        qDebug() << e.getVirtualCenter();
//        qDebug() << e.transformation();
        e.draw(renderer);
    }
    m_playership->draw(renderer);
}

void GameEngine::processEntities()
{
    for (int i = 0; i < bulletContainer().size(); i++){
        Bullet& b = m_bulletContainer[i];
        //### diese berechnung is fail weil coordinatensystem is anders nach dem call von setRotationDirection
//        QVector3D d = b.direction();
//        d.normalize();
//        d = d * b.velocity();
//        qDebug() << d;
//        qDebug() << b.direction() << b.getVirtualCenter() << b.velocity();
        b.translate(v_Y * b.velocity());
        qDebug() <<b.transformation();
    }
    qDebug() << "==========================================";
    if (bulletContainer().size() >= 2){
        qDebug() << bulletContainer().at(0).transformation();
        qDebug() << bulletContainer().at(1).transformation();
    }
}

void GameEngine::snycEntities()
{
    for (int i = 0; i < bulletContainer().size(); i++){
        Bullet& b = m_bulletContainer[i];
        b.snycForRendering();
    }
    m_playership->snycForRendering();
}

void GameEngine::addBullet(Bullet bullet)
{
    m_bulletContainer.append(bullet);
}

void GameEngine::deleteBullet(Bullet bullet)
{
    if (m_bulletContainer.removeOne(bullet))
        qDebug() << "bullet removed from bulletcontainer";
    else
        qDebug() << "can not remove item from bulletcontainer";
}

GLBullet *GameEngine::glbulletgreen() const
{
    return m_glbulletgreen;
}

void GameEngine::setGlbulletgreen(GLBullet *glbulletgreen)
{
    m_glbulletgreen = glbulletgreen;
}

GLBullet *GameEngine::glbulletred() const
{
    return m_glbulletred;
}

void GameEngine::setGlbulletred(GLBullet *glbulletred)
{
    m_glbulletred = glbulletred;
}

QList<Bullet> GameEngine::bulletContainer()
{
    return m_bulletContainer;
}

Spaceship* GameEngine::playership()
{
    return m_playership;
}

void GameEngine::shootWithPlayerShip()
{
    if (playership()->isReadyToShoot()){
        QVector3D v = playership()->getVirtualCenter();
        spawnBullet(v + QVector3D(2.0,4.0,0.5) , QVector3D(0.0,0.0,1.0), 0.2);
        spawnBullet(v + QVector3D(-2.0,4.0,0.5) , QVector3D(0.0,0.0,1.0), 0.2);
        playership()->shoot();
    }else{
        qDebug() << "cant shoot yet with with , Weapons are on cooldown";
    }
}

void GameEngine::spawnBullet(QVector3D location, QVector3D direction, double velocity)
{
    qDebug() << "appending bullet";
    Bullet b = Bullet(this,glbulletred(),velocity,direction,location);
    b.setRotationDirection(direction);
    addBullet(b);
}
