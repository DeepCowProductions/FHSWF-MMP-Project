#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QTimer>

#include "../globjects/glbullet.h"
#include "../globjects/glspaceship.h"
#include "../globjects/glsphere.h"
#include "../sound/soundengine.h"
#include "definesandconstants.h"
#include "bullet.h"
#include "spaceship.h"
#include "smallenemy.h"
#include "singleshottimer.h"

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

    void drawEntities(GLESRenderer *renderer);
    void processEntities();

    void processGameTickCooldowns();
    void spawnRandomEnemies ();
    void staticCollisionDetection();
    void moveAutomaticEntities();
    void deleteMarkedEntities();
    void shootWithAutomaticEntities();

    void snycEntities();

    void toggleEnemyMovementDirection();

    void addRedBullet(Bullet bullet);
    bool deleteRedBullet(Bullet bullet);
    void addGreenBullet(Bullet bullet);
    bool deleteGreenBullet(Bullet bullet);
    void addEnemy(SmallEnemy e);
    bool deleteEnemy(SmallEnemy e);

    void setSoundEngineEnabled(bool on);

    GLBullet *glbulletgreen() const;
    void setGlbulletgreen(GLBullet *glbulletgreen);

    GLBullet *glbulletred() const;
    void setGlbulletred(GLBullet *glbulletred);

    QList<Bullet> bulletContainerRed();
    Spaceship * playership();
    QList<Bullet> bulletContainerGreen();
    QList<SmallEnemy> enemyConatiner();

    void setEffectsOn(bool on);

signals:
    void smallEnemyKilled (int value, QVector3D location);
    void bigEnemyKilled (int value, QVector3D location);
    void playershipHit(int value);

public slots:
    void shootWithPlayerShip();

    void spawnRedBullet(QVector3D location , QVector3D direction, double velocity);
    void spawnGreenBullet (QVector3D location , QVector3D direction,  double velocity);
    void spawnEnemy(QVector3D location);

    //    void onObjectDestroyed(QObject* obj = 0);

private:
    //### Entities aks actual objects in game
    Spaceship * m_playership;
    QList<Bullet> m_bulletContainerRed;
    QList<Bullet> m_bulletContainerGreen;
    QList<SmallEnemy> m_enemyConatiner;

    //### enemy lanes
    int m_numberOfLanes = 0;
    QMap<int,SingleShotTimer*> m_laneSpawningCooldowns;
    SingleShotTimer m_enemyMovementStateTimer;
    bool m_enemyMovementState; // 0 for left, 1 for right

    //### holds indicies wich should be deleted in the next frame
    QList<Bullet*> rbDelMarks;
    QList<Bullet*> gbDelMarks;
    QList<SmallEnemy*> enDelMarks;

    //### from GLBody derived VAO models
    GLBullet * m_glbulletgreen;
    GLBullet * m_glbulletred;
    GLSpaceShip * m_glsppaceship;
    GLSphere * m_glsphere;

    // simple not very good objects for effects
    GLSphere * m_explosionSphere;

    //### boundingBoxes of variusObjects
    TAABB * m_bulletBounding;
    TAABB * m_smallEnemyBounding;

    SoundEngine * m_soundEngine;
    bool m_effectsOn;
};

#endif // GAMEENGINE_H
