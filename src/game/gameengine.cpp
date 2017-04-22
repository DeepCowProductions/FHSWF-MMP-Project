#include "gameengine.h"

GameEngine::GameEngine(QObject *parent) : QObject(parent)
{
    //### init glObjects
    m_glbulletgreen = new GLBullet("green bullet",3.0,0.2,GLColorRgba::clGreen,"");
    m_glbulletred = new GLBullet("red bullet",3.0,0.2,GLColorRgba::clRed,"");
    m_glsphere = new GLSphere("placeHolder",3.0);
    m_glsppaceship = new GLSpaceShip("3D Spaceship / PlayersShip");
    m_glsppaceship->setTextureFile(":/spaceshipTex"); // use alias
    m_explosionSphere = new GLSphere("redSphere",3.0,GLColorRgba::clRed);

    m_bulletBounding = new TAABB(QVector3D(m_glbulletred->diamenter(),m_glbulletred->length(),m_glbulletred->diamenter()),
                                 QVector3D(-m_glbulletred->diamenter(),-m_glbulletred->length(),-m_glbulletred->diamenter()));

    // init starting Entities
    m_playership = new Spaceship(this, m_glsppaceship);

    m_numberOfLanes = ((int)( Spaceinvaders::playFieldBounds * 2 ))/((int)Spaceinvaders::laneWidth);
    for (int i=0; i<m_numberOfLanes; i++){
        SingleShotTimer* timer = new SingleShotTimer();
        timer->setCooldown(Spaceinvaders::enemySpawnCooldownPerLane);
        m_laneSpawningCooldowns.insert(i,timer);
    }
    m_enemyMovementStateTimer.setCooldown(Spaceinvaders::enemyTicksBeforeChangingDirection);
}

GameEngine::~GameEngine()
{
    m_bulletContainerRed.clear();

    for (int i=0; i<m_numberOfLanes; i++){
        SingleShotTimer* t = m_laneSpawningCooldowns.value(i);
        delete t;
    }
    m_laneSpawningCooldowns.clear();

    if (m_glbulletgreen)
        delete m_glbulletgreen;
    if (m_glbulletred)
        delete m_glbulletred;

    // TBI

}

void GameEngine::drawEntities(GLESRenderer *renderer)
{
    for (int i=0; i < m_bulletContainerRed.size();i++){
        m_bulletContainerRed[i].draw(renderer);
    }
    for (int i=0; i < m_bulletContainerGreen.size();i++){
        m_bulletContainerGreen[i].draw(renderer);
    }
    for (int i = 0; i < m_enemyConatiner.size(); i++){
        m_enemyConatiner[i].draw(renderer);
    }
    m_playership->draw(renderer);
}

void GameEngine::processEntities()
{
    //    qDebug() << "GameEngine::processEntities() started";
    //    qDebug() << "==========================================";
    processGameTickCooldowns();
    spawnRandomEnemies();
    moveAutomaticEntities();
    staticCollisionDetection();
    shootWithAutomaticEntities();
    deleteMarkedEntities();

    //    qDebug() << "==========================================";
    //    qDebug() << "GameEngine::processEntities() finished";
}


void GameEngine::spawnRandomEnemies()
{

    for (int i = 0; i < m_numberOfLanes; i++) {
        if (m_laneSpawningCooldowns.value(i)->isReadyToShoot())
            if (qrand()%100 < Spaceinvaders::chanceOfEnemySpawningPerLane){
                int r = (-Spaceinvaders::playFieldBounds) + i * (((int)(Spaceinvaders::playFieldBounds*2))/m_numberOfLanes);
                spawnEnemy(QVector3D(r,0.0,Spaceinvaders::playFieldLength));
                m_laneSpawningCooldowns.value(i)->shoot();
            }
    }

}

void GameEngine::staticCollisionDetection()
{
    // playership with enemy bullets (green):
    for (int i = 0; i < m_bulletContainerGreen.size(); i++) {
        if (playership()->checkCollision(&m_bulletContainerGreen[i])) {
            gbDelMarks.append(&m_bulletContainerGreen[i]);
            emit playershipHit(1);
        }
    }

    // enemyships with player bullets (red):
    for (int i = 0; i < m_enemyConatiner.size(); i++) {
        for (int j = 0; j < m_bulletContainerRed.size(); j++) {
            if (m_enemyConatiner[i].checkCollision(&m_bulletContainerRed[j])) {
                enDelMarks.append(&m_enemyConatiner[i]);
                rbDelMarks.append(&m_bulletContainerRed[j]);
                j++;
                emit smallEnemyKilled(10,m_enemyConatiner[i].getVirtualCenter());
            }
        }
    }
}

void GameEngine::moveAutomaticEntities()
{
    for (int i = 0; i < m_bulletContainerRed.size(); i++){
        //        Bullet& b = m_bulletContainerRed[i];
        //### diese berechnung is falsch weil Koordinatensystem ist anders nach dem call von setRotationDirection
        //        QVector3D d = b.direction();
        //        d.normalize();
        //        d = d * b.velocity();
        //        qDebug() << d;
        //        qDebug() << b.direction() << b.getVirtualCenter() << b.velocity();

        //### deshalb -> movement in null richtung der bullets:
        m_bulletContainerRed[i].translate(v_Y * m_bulletContainerRed[i].velocity());
        //        qDebug() <<b.transformation();


        //### check if bullets is out of bounds
#ifdef Q_OS_ANDROID
        if (m_bulletContainerRed[i].getVirtualCenter().z() > Spaceinvaders::playFieldLength + Spaceinvaders::playFieldBuffer) {
            //            deleteRedBullet(b); // deleting directly confuses the QList, but still works with some minor errors
            //            rbDelMarks.append(i);
            rbDelMarks.append(&m_bulletContainerRed[i]);
        }
#else
        if (m_bulletContainerRed[i].getVirtualCenter().z() > Spaceinvaders::playFieldLength + Spaceinvaders::playFieldBuffer ) {
            //            deleteRedBullet(b); // deleting directly confuses the QList, but still works with some minor errors
            //            rbDelMarks.append(i);
            rbDelMarks.append(&m_bulletContainerRed[i]);
        }
#endif
    }

    for (int i = 0; i < m_bulletContainerGreen.size(); i++){
        m_bulletContainerGreen[i].translate(v_Y * m_bulletContainerGreen[i].velocity());
#ifdef Q_OS_ANDROID
        if (m_bulletContainerGreen[i].getVirtualCenter().z() < -Spaceinvaders::playFieldBuffer ) {
            gbDelMarks.append(&m_bulletContainerRed[i]);
        }
#else
        if (m_bulletContainerGreen[i].getVirtualCenter().z() < -Spaceinvaders::playFieldBuffer) {
            gbDelMarks.append(&m_bulletContainerGreen[i]);
        }
#endif
    }

    if (m_enemyMovementStateTimer.isReadyToShoot()){
        m_enemyMovementStateTimer.shoot();
        toggleEnemyMovementDirection();
    }
    for (int i = 0; i < m_enemyConatiner.size(); i++){
        if (m_enemyMovementState)
            m_enemyConatiner[i].translate(QVector3D(-Spaceinvaders::enemyMovmentSpeedinX,0.0,-Spaceinvaders::enemyMovmentSpeedinZ));
        else
            m_enemyConatiner[i].translate(QVector3D(+Spaceinvaders::enemyMovmentSpeedinX,0.0,-Spaceinvaders::enemyMovmentSpeedinZ));
    }

}

void GameEngine::deleteMarkedEntities()
{
    //### SIDE NOTE:
    /* Better way of deleting items would be to only save indicies for deleting
     * within an ordered list and then remove items at indicies with respect of how many items are to be deleted
     * (because the size of the list changes ....)
     *
     * Current version utilises the QList function delete(...) wich claims to be somewhat efficient,
     * however it compares items with the == operator and travels throw the list -> O(n) for every item wich shall be deleted.
     *
     * Using only indicies and a clever data structure to hold out game entities this could propably be done in O(1).
     * Since we are only managing a small number of items this solution should still be ok.
     */
    for (int i = 0; i < rbDelMarks.size(); i++){
        //        if (!deleteRedBullet(m_bulletContainerRed[rbDelMarks.at(i)-i])) // only works if the array is an orderd list
        //            qDebug() << "somthing went wrong woth deletion";
        deleteRedBullet(*rbDelMarks.at(i));
    }

    for (int i = 0; i < gbDelMarks.size(); i++){
        //        if(!deleteGreenBullet(m_bulletContainerGreen[gbDelMarks.at(i)-i])) // only works if the array is an orderd list
        //            qDebug() << "somthing went wrong woth deletion";
        deleteGreenBullet(*gbDelMarks.at(i));
    }

    for (int i = 0; i < enDelMarks.size(); i++){
        //        if(!deleteEnemy(m_enemyConatiner[enDelMarks.at(i)-i])) // only works if the array is an orderd list
        //            qDebug() << "somthing went wrong woth deletion";
        deleteEnemy(*enDelMarks.at(i));
    }
    rbDelMarks.clear();
    gbDelMarks.clear();
    enDelMarks.clear();
}

void GameEngine::shootWithAutomaticEntities()
{
    QVector3D d(0.0,0.0,3.0);
    //    qDebug() << "shoooting ai at random";
    for (int i = 0; i < m_enemyConatiner.size(); i++) {
        if (m_enemyConatiner[i].isReadyToShoot()){
            if (qrand()%10 > 8){
                m_enemyConatiner[i].shoot();
                spawnGreenBullet(m_enemyConatiner[i].getVirtualCenter()-d,-v_Z,Spaceinvaders::enemyBulletSpeed);
            }
        }
    }
}

void GameEngine::processGameTickCooldowns()
{
    playership()->doCooldownTick();
    for (int i = 0; i < m_enemyConatiner.size(); i++){
        m_enemyConatiner[i].doCooldownTick();
    }

    for (int i=0; i<m_numberOfLanes; i++){
        m_laneSpawningCooldowns.value(i)->doCooldownTick();
    }

    m_enemyMovementStateTimer.doCooldownTick();
}

void GameEngine::snycEntities()
{
    for (int i = 0; i < m_bulletContainerRed.size(); i++){
        m_bulletContainerRed[i].snycForRendering();
    }
    for (int i = 0; i < m_bulletContainerGreen.size(); i++){
        m_bulletContainerGreen[i].snycForRendering();
    }
    for (int i = 0; i < m_enemyConatiner.size(); i++){
        m_enemyConatiner[i].snycForRendering();
    }
    m_playership->snycForRendering();
}

void GameEngine::toggleEnemyMovementDirection()
{
    if (m_enemyMovementState)
        m_enemyMovementState = false;
    else
        m_enemyMovementState = true;
}

void GameEngine::addRedBullet(Bullet bullet)
{
    m_bulletContainerRed.append(bullet);
    //    qDebug() << "item appended to m_bulletContainerRed";
}

bool GameEngine::deleteRedBullet(Bullet bullet)
{
    if (m_bulletContainerRed.removeOne(bullet)) {
        //        qDebug() << "item removed from m_bulletContainerRed";
        return true;
    }
    qDebug() << "can not remove item from m_bulletContainerRed";
    return false;
}

void GameEngine::addGreenBullet(Bullet bullet)
{
    m_bulletContainerGreen.append(bullet);
    //    qDebug() << "item appended to m_bulletContainerGreen";
}

bool GameEngine::deleteGreenBullet(Bullet bullet)
{
    if (m_bulletContainerGreen.removeOne(bullet)){
        //        qDebug() << "item removed from m_bulletContainerGreen";
        return true;
    }
    qDebug() << "can not remove item from m_bulletContainerGreen";
    return false;
}

void GameEngine::addEnemy(SmallEnemy e)
{
    m_enemyConatiner.append(e);
    //    qDebug() << "item appended to m_enemyConatiner";
}

bool GameEngine::deleteEnemy(SmallEnemy e)
{
    if (m_enemyConatiner.removeOne(e)){
        //        qDebug() << "item removed from m_enemyConatiner";
        return true;
    }
    qDebug() << "can not remove item from m_enemyConatiner";
    return false;
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

QList<Bullet> GameEngine::bulletContainerRed()
{
    return m_bulletContainerRed;
}

QList<SmallEnemy> GameEngine::enemyConatiner()
{
    return m_enemyConatiner;
}

QList<Bullet> GameEngine::bulletContainerGreen()
{
    return m_bulletContainerGreen;
}

Spaceship* GameEngine::playership()
{
    return m_playership;
}

void GameEngine::shootWithPlayerShip()
{
    if (playership()->isReadyToShoot()){
        QVector3D v = playership()->getVirtualCenter();
        spawnRedBullet(v + QVector3D(2.0,1.0,0.5) , QVector3D(0.0,0.0,1.0), Spaceinvaders::playerBulletSpeed);
        spawnRedBullet(v + QVector3D(-2.0,1.0,0.5) , QVector3D(0.0,0.0,1.0), Spaceinvaders::playerBulletSpeed);
        playership()->shoot();
    }else{
        qDebug() << "cant shoot yet with with , Weapons are on cooldown";
    }
}

void GameEngine::spawnRedBullet(QVector3D location, QVector3D direction, double velocity)
{
    //    qDebug() << "appending red bullet";
    Bullet b = Bullet(this,glbulletred(),velocity,direction,location,m_bulletBounding);
    b.setRotationDirection(direction);
    addRedBullet(b);
}

void GameEngine::spawnGreenBullet(QVector3D location, QVector3D direction, double velocity)
{
    //    qDebug() << "appending green bullet";
    Bullet b = Bullet(this,glbulletgreen(),velocity,direction,location,m_bulletBounding);
    b.setRotationDirection(direction);
    addGreenBullet(b);
}

void GameEngine::spawnEnemy(QVector3D location)
{
    //    qDebug() << "appending SmallEnemy";
    SmallEnemy e = SmallEnemy(this,m_glsphere);
    e.setCurrentCooldownTick(Spaceinvaders::enemyShootingCooldownInGameTicks);
    e.setVirtualCenter(location);
    addEnemy(e);
}


