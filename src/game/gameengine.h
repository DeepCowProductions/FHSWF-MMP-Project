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
 *        Controls all major game logic and holds/manages GameEnities.
 *
 * This class is supposed to be used in conjuction with a class or subclass of type GLItem.
 *
 * each loop of the game wich is controlled by a timer outside of this class
 *  GameEngine::processEntities() gets called and performs the following opeartions in tis order:
 * @code
 *   processGameTickCooldowns();
 *   spawnRandomEnemies();
 *   moveAutomaticEntities();
 *   staticCollisionDetection();
 *   shootWithAutomaticEntities();
 *   deleteMarkedEntities();
 * @endcode
 *  To apply the new transformation Matricies call:
 * @code
 *  GameEngine::snycEntities()
 * @endcode
 *  After this the next frame can draw the changes of the past GameTick by calling:
 * @code
 *  GameEngine::drawEntities(GLESRenderer *renderer)
 * @endcode
 *
 * This class was written to seperate most game logik from the gamesceen item wich gets displayed by the qml gui.
 * It can be (and is currently) used with two seprerate QTimers for controlling framerate and gameticktate.
 * (framerate timer is inside GLItem : GLItem::m_timer, timer for ticks is GameSceen: GameSceen::m_timer_gameloop)
 * When used with the qml sceengraph this stucture is supposed to threadsave in the future, however currently it is not entirly threadsave.
 *
 * To make it threadsae in the future, one has to completely encapsulate and controll all access to the members and functions accordingly.
 * Right now for example, movement of player controlled GameEntities is directly managed by GameSceen and the signals from the gui.
 * Unfortunetly we do not have the time to implement thoose features right now.
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = 0);
    virtual ~GameEngine();

    /**
     * @brief gameOver sounds a SoundEffect when the game is over
     */
    void gameOver();

    /**
     * @brief drawEntities draws the Entities with the overgiven renderer
     * @param renderer
     */
    void drawEntities(GLESRenderer *renderer);

    /**
     * @brief processEntities starts some functions, which are for the gamelogic,
     *        like collisiondetection or function for moving the enemy
     */
    void processEntities();

    /**
     * @brief processGameTickCooldowns cools down all timer of the game
     */
    void processGameTickCooldowns();

    /**
     * @brief spawnRandomEnemies is for spawning the enemies randomlly automaticlly
     */
    void spawnRandomEnemies ();

    /**
     * @brief staticCollisionDetection checks if a bullet hits the player or a enemy,
     * also if the player collides with a enemy.
     *
     * If someone is collieded, than set the entity as to delete and emit a signal.
     */
    void staticCollisionDetection();

    /**
     * @brief moveAutomaticEntities is for start moving the enemies automaticlly
     */
    void moveAutomaticEntities();

    /**
     * @brief deleteMarkedEntities is for deleting the marked Entities
     */
    void deleteMarkedEntities();

    /**
     * @brief shootWithAutomaticEntities is for that the enemies shoots automaticlly
     */
    void shootWithAutomaticEntities();

    /**
     * @brief snycEntities is for that to sync all entities for rendering
     */
    void snycEntities();

    /**
     * @brief toggleEnemyMovementDirection is for that to toogle the movedirection
     * of the enemy
     */
    void toggleEnemyMovementDirection();

    /**
     * @brief addRedBullet is for adding a red bullet to his container
     * @param bullet bullet which want to add
     */
    void addRedBullet(Bullet bullet);

    /**
     * @brief deleteRedBullet is for deleting a red bullet from his container
     * @param bullet which want to delete from his container
     * @return if the bullet was deleted
     */
    bool deleteRedBullet(Bullet bullet);

    /**
     * @brief addGreenBullet is for adding a green bullet to his container
     * @param bullet which want to add
     */
    void addGreenBullet(Bullet bullet);

    /**
     * @brief deleteRedBullet is for deleting a green bullet from his container
     * @param bullet which want to delete from his container
     * @return if the bullet was deleted
     */
    bool deleteGreenBullet(Bullet bullet);

    /**
     * @brief addEnemy for adding a enemy to the enemeycontainer
     * @param e(enemy) which want to add
     */
    void addEnemy(SmallEnemy e);

    /**
     * @brief deleteEnemy for deleting a enemy from the enemycontainer
     * @param e(enemy) which want to delete
     * @return if deleting the enemy was successfull
     */
    bool deleteEnemy(SmallEnemy e);

    /**
     * @brief enemy returns the enemy
     * @return GLSpacShip
     */
    GLSpaceShip * enemy();

    /**
     * @brief setSoundEngineEnabled sets the SoundEngine enabled
     * @param on true or false
     */
    void setSoundEngineEnabled(bool on);

    /**
     * @brief glbulletgreen getter for green bullet
     * @return the green bullet
     */
    GLBullet *glbulletgreen() const;

    /**
     * @brief setGlbulletgreen setter for green bullet
     * @param glbulletgreen
     */
    void setGlbulletgreen(GLBullet *glbulletgreen);

    /**
     * @brief glbulletred getter for red bullet
     * @return the red bullet
     */
    GLBullet *glbulletred() const;

    /**
     * @brief setGlbulletred setter for red bullet
     * @param glbulletred
     */
    void setGlbulletred(GLBullet *glbulletred);

    /**
     * @brief bulletContainerRed Container for the red bullets
     * @return a list with all red bullets
     */
    QList<Bullet> bulletContainerRed();

    /**
     * @brief playership getter for the players ship
     * @return the players ship
     */
    Spaceship * playership();

    /**
     * @brief bulletContainerGreen Container for the green bullets
     * @return a list of all green bullets
     */
    QList<Bullet> bulletContainerGreen();

    /**
     * @brief enemyConatiner Container for the enemies
     * @return a list of all enemies
     */
    QList<SmallEnemy> enemyConatiner();

    /**
     * @brief setEffectsOn is for that to switch sound effects on and off
     * @param on true or false
     */
    void setEffectsOn(bool on);

signals:
    /**
     * @brief smallEnemyKilled a signal which emits when a enemy was killed
     * @param value points for a enemy
     * @param location where the enemy was
     */
    void smallEnemyKilled (int value, QVector3D location);

    /**
     * @brief bigEnemyKilled a signal which emits when a boss was killed
     * @param value points for the boss
     * @param location where the boss was
     */
    void bigEnemyKilled (int value, QVector3D location);

    /**
     * @brief playershipHit a signal which emits when the player was hit
     */
    void playershipHit();

public slots:
    /**
     * @brief shootWithPlayerShip is for shooting with the players ship, here
     * we spawn 2 red bullets
     */
    void shootWithPlayerShip();

    /**
     * @brief spawnRedBullet is for spawning a red bullet at one point and in one direction,
     *        with a velocity
     * @param location where to spawn
     * @param direction in which they fly
     * @param velocity
     */
    void spawnRedBullet(QVector3D location , QVector3D direction, double velocity);

    /**
     * @brief spawnRedBullet is for spawning a green bullet at one point and in one direction,
     *        with a velocity
     * @param location where to spawn
     * @param direction in which they fly
     * @param velocity
     */
    void spawnGreenBullet (QVector3D location , QVector3D direction,  double velocity);

    /**
     * @brief spawnEnemy spawns enemy and add to container
     * @param location where want to spawn
     */
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
    GLSpaceShip * m_glenemyspaceship;

    // simple not very good objects for effects
    GLSphere * m_explosionSphere;

    //### boundingBoxes of variusObjects
    TAABB * m_bulletBounding;
    TAABB * m_smallEnemyBounding;

    //### SoundEngine for sound effects
    SoundEngine * m_soundEngine;
    bool m_effectsOn;

};

#endif // GAMEENGINE_H
