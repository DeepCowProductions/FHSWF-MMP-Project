#ifndef DEFINESANDCONSTANTS_H
#define DEFINESANDCONSTANTS_H

#include <QVector3D>

/**
 * @brief collection of random util functions and
 */
namespace Spaceinvaders {

//### Constance for the Game
//### in the future: configurable by the game's player -> put theese constance into a class and make them accessable

//const static QVector3D v_normalOrientation = QVector3D(0.0, 1.0, 0.0);
const static int AndroidSkyBoxRadius = 120;
const static int DesktopSkyBoxRadius = 60;
const static QVector3D AndroidViewVector = QVector3D(80, 10, 400); // (eyeDistance,near,far)
const static QVector3D DesktopViewVector = QVector3D(40, 10, 200); // (eyeDistance,near,far)
const static QVector3D ViewDirection = -QVector3D(0.0,-0.5,1.0);   // eyePos
const static int GameTickCooldownInMillSec = 50;
const static int RenderTickCooldownInMillSec = 50;
const static QVector3D staticLightDirection = QVector3D(1.0, 1.0, 1.0);

const static float playFieldLength = 110.0;
const static float playFieldBounds = 30.0;
const static float playFieldLengthBuffer = 22.0;
const static float laneWidth = 9.0;
const static float laneOffSet = 5.0;
const static int   chanceOfEnemySpawningPerLane = 100;
const static int   enemySpawnCooldownPerLane = 100;
const static int   enemyShotingChancePerTick = 10;
const static int   enemyShootingCooldownInGameTicks = 100;
const static int   playerShootingCooldownInGameTicks = 20;
const static float enemyBulletSpeed = 2.0;
const static float playerBulletSpeed = 2.0;
const static float playerShipMovementSpeed = 1.0;
const static int   enemyTicksBeforeChangingDirection = 100;
const static float enemyMovmentSpeedinX = 0.15;
const static float enemyMovmentSpeedinZ = 0.2;

/**
 * @brief clamp clamps a value between a and b.
 * examples: (42,3,5) -> 5 || (4,2,5) -> 4  || (1,3,5) -> 3.
 * @param x value to clamp
 * @param a lower bound
 * @param b upper bound
 * @return adjusted value
 */
inline float clamp(float x, float a, float b)   {   return x < a ? a : (x > b ? b : x); }
/**
 * @brief sqr sqares a number.
 * @param x number to sqare
 * @return sqare of that number
 */
inline float sqr(float x)   {   return x*x; }

}

#endif // DEFINESANDCONSTANTS_H
