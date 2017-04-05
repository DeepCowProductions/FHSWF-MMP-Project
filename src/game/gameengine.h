#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QTimer>

#include "../globjects/glbullet.h"
#include "../globjects/glspaceship.h"
#include "../globjects/glsphere.h"
#include "bullet.h"
#include "spaceship.h"

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

    void addBullet(Bullet bullet);
    void deleteBullet(Bullet bullet);

    GLBullet *glbulletgreen() const;
    void setGlbulletgreen(GLBullet *glbulletgreen);

    GLBullet *glbulletred() const;
    void setGlbulletred(GLBullet *glbulletred);

    QList<Bullet> bulletContainer();
    Spaceship * playership();


signals:

public slots:

    void shootWithPlayerShip();

    void spawnBullet(QVector3D location , QVector3D direction, double velocity);

    //    void onObjectDestroyed(QObject* obj = 0);

private:
    //### Entities aks actual objects in game
    Spaceship * m_playership;
    QList<Bullet> m_bulletContainer;
//    std::vector<GLBody*> m_enemyConatiner;

    //### from GLBody derived VAO models
    GLBullet * m_glbulletgreen;
    GLBullet * m_glbulletred;
    GLSpaceShip * m_glsppaceship;
    GLSphere * m_glsphere;


};

#endif // GAMEENGINE_H
