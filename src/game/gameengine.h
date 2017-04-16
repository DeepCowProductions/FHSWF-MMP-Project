#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QTimer>

#include "../globjects/glbullet.h"
#include "../globjects/glspaceship.h"
#include "../globjects/glsphere.h"
#include "definesandconstants.h"
#include "bullet.h"
#include "spaceship.h"
#include "smallenemy.h"

/**
 * @brief The GameEngine class
 *        Controls all major game logic.
 *
 * @attention A Comment is with ### after // marked and written UPPERCASE.
 *
 * [...]
 *
 */
class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = 0);
    virtual ~GameEngine();

    virtual void drawEntities(GLESRenderer *renderer);
    virtual void processEntities();
    virtual void snycEntities();

    void addRedBullet(Bullet bullet);
    bool deleteRedBullet(Bullet bullet);
    void addGreenBullet(Bullet bullet);
    bool deleteGreenBullet(Bullet bullet);
    void addEnemy(SmallEnemy e);
    bool deleteEnemy(SmallEnemy e);

    GLBullet *glbulletgreen() const;
    void setGlbulletgreen(GLBullet *glbulletgreen);

    GLBullet *glbulletred() const;
    void setGlbulletred(GLBullet *glbulletred);

    QList<Bullet> bulletContainerRed();
    Spaceship * playership();
    QList<Bullet> bulletContainerGreen();
    QList<SmallEnemy> enemyConatiner();

signals:

public slots:

    void shootWithPlayerShip();

    void spawnRedBullet(QVector3D location , QVector3D direction, double velocity);
    void spawnEnemy(QVector3D location);

    //    void onObjectDestroyed(QObject* obj = 0);

private:
    //### Entities aks actual objects in game
    Spaceship * m_playership;
    QList<Bullet> m_bulletContainerRed;
    QList<Bullet> m_bulletContainerGreen;
    QList<SmallEnemy> m_enemyConatiner;

    //### holds indicies wich should be deleted in the next frame
    QList<Bullet*> rbDelMarks;
    QList<Bullet*> gbDelMarks;
    QList<SmallEnemy*> enDelMarks;

    //### from GLBody derived VAO models
    GLBullet * m_glbulletgreen;
    GLBullet * m_glbulletred;
    GLSpaceShip * m_glsppaceship;
    GLSphere * m_glsphere;

    //### boundingBoxes of variusObjects
    TAABB * m_bulletBounding;
    TAABB * m_smallEnemyBounding;
//    TAABB * m_spaceshipBounding1;
//    TAABB * m_spaceshipBounding2;
//    TAABB * m_spaceshipBounding3;


};

#endif // GAMEENGINE_H
