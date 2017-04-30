#ifndef GAMESCEEN_H
#define GAMESCEEN_H

#include "../glcore/glitem.h"
#include "../globjects/glspaceship.h"
#include "../globjects/glfrustum.h"
#include "../globjects/glmouseray.h"
#include "../globjects/glskybox.h"
#include "../glcore/shaderdebugger.h"
#include "../glcore/skyboxrenderer.h"
#include "../globjects/glcube.h"
#include "../sound/soundengine.h"
#include "../sound/qgamemusicengine.h"
#include "gameengine.h"
#include "definesandconstants.h"
#include <QDesktopWidget>
#include <QScreen>
#include <QGuiApplication>
#include <QQuickWindow>
#include <QShortcut>
#include <QtMath>

/**
 * @brief The GameSceen class
 *  QQuickItem used to display our Spaceinvaders game, to be used within qml.
 *
 * This class takes care of some initialisation and primarly the controlls for the game (i.e. user input).
 *
 *
 * @attention A Comment is with ### after // marked.
 *
 * @author Kuhmichel(1004128)
 * @author Grabelus(10044563)
 */
class GameSceen : public GLItem
{
    Q_OBJECT
    //### PROPERTIES OF THE SPACEINVADERS. QML FOR INTERACTING
    Q_PROPERTY(bool gameOver READ gameOver WRITE setGameOver NOTIFY gameOverChanged)
    Q_PROPERTY(bool newGame READ newGame WRITE setNewGame NOTIFY newGameChanged)
    Q_PROPERTY(bool effectsOn READ EffectsOn WRITE setEffectsOn NOTIFY EffectsOnChanged)
    Q_PROPERTY(bool musicOn READ musicOn WRITE setMusicOn NOTIFY musicOnChanged)
    Q_PROPERTY(bool isTablet READ isTablet WRITE setIsTablet NOTIFY isTabletChanged)
    Q_PROPERTY(bool shotButtonPressed READ shotButtonPressed WRITE setShotButtonPressed NOTIFY shotButtonPressedChanged)
    Q_PROPERTY(bool firstLife READ firstLife WRITE setFirstLife NOTIFY firstLifeChanged)
    Q_PROPERTY(bool secLife READ secLife WRITE setSecLife NOTIFY secLifeChanged)
    Q_PROPERTY(bool thirdLife READ thirdLife WRITE setThirdLife NOTIFY thirdLifeChanged)
    Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged)
    Q_PROPERTY(bool leftKeyPressed READ leftKeyPressed WRITE setLeftKeyPressed NOTIFY leftKeyPressedChanged)
    Q_PROPERTY(bool rightKeyPressed READ rightKeyPressed WRITE setRightKeyPressed NOTIFY rightKeyPressedChanged)
    Q_PROPERTY(bool runGameLoop READ runGameLoop WRITE setRunGameLoop NOTIFY runGameLoopChanged)

public:
    /**
     * @brief GameSceen
     * Constructor, initialises gamesceen and connects signals.
     */
    GameSceen(QQuickItem *parent = 0);
    ~GameSceen();

    /**
     * @brief isTablet for use in this class to detect, if is a Tablet or Smartphone(is used for QML)
     * @return
     */
    bool isTablet();

    /**
     * @brief keyCounter for detecting if key pressed
     */
    int keyCounter =0;

    /**
     * @brief leftKeyPressed returns if the "left" key or "a" was pressed
     *
     * @return boolean value
     */
    bool leftKeyPressed() const {   return m_leftKeyPressed;    }

    /**
     * @brief rightKeyPressed returns if the "right" key or "d" was pressed
     *
     * @return boolean value
     */
    bool rightKeyPressed() const {   return m_rightKeyPressed;    }

    /**
     * @brief firstLife returns if the player have his first life
     * @return  boolean value
     */
    bool firstLife() const {   return m_firstLife;    }

    /**
     * @brief secLife returns if the player have his second life
     * @return  boolean value
     */
    bool secLife() const {   return m_secLife;    }

    /**
     * @brief thirdLife returns if the player have his third life
     * @return  boolean value
     */
    bool thirdLife() const {   return m_thirdLife;    }

    /**
     * @brief score returns the score of the player
     * @return int
     */
    int score() const {   return m_score;    }

    /**
     * @brief runGameLoop returns if the gameloop is running
     * @return boolean value
     */
    bool runGameLoop() const {  return m_runGameLoop;   }

    /**
     * @brief gameEngine returns the GameEngine of the current game
     * @return  GameEngine
     */
    GameEngine *gameEngine() const;

    /**
     * @brief shotButtonPressed returns if the shotButton was pressed
     * @return boolean value
     */
    bool shotButtonPressed() const;

    /**
     * @brief musicOn returns if the user has set the music on
     * @return boolean value
     */
    bool musicOn() const    {   return m_musicOn;   }

    /**
     * @brief EffectsOn returns if the user has set the effects on
     * @return boolean value
     */
    bool EffectsOn() const  {   return m_effectsOn; }

    /**
     * @brief newGame returns if the a new game is started
     * @return boolean value
     */
    bool newGame() const  {   return m_newGame; }

    /**
     * @brief gameOver returns if the game is over, by loosing
     * @return boolean value
     */
    bool gameOver() const  {   return m_gameOver; }

public slots:
    /**
     * @brief resetView slot for reseting the view.
     *        Currently only called when setting up the first frame.
     *        Other moments for use may be implemented later.
     */
    void resetView();

    /**
     * @brief gameloopTimeout controlls timedependend operations, seperate from updateWindow().
     */
    void onTimer_GameLoopTimeout();
    virtual void gameLoopTimeout();
    virtual void timerTimeout();

    /**
     * @brief setLeftKeyPressed checks if the "left" or "a" key is pressed.
     *        check if the bool value for the keypress has changed,
     *        if yes emit a signal.
     *
     * @param leftKeyPressed bool
     */
    void setLeftKeyPressed(bool leftKeyPressed);

    /**
     * @brief setRightKeyPressed checks if the "right" or "d" key is pressed.
     *        check if the bool value for the keypress has changed,
     *        if yes emit a signal.
     *
     * @param rightKeyPressed bool
     */
    void setRightKeyPressed(bool rightKeyPressed);

    /**
     * @brief setFirstLife sets the first life of the player on true or false
     * @param firstLife
     */
    void setFirstLife(bool firstLife);

    /**
     * @brief setSecLife sets the second life of the player on true or false
     * @param secLife
     */
    void setSecLife(bool secLife);

    /**
     * @brief setThirdLife sets the third life of the player on true or false
     * @param thirdLife
     */
    void setThirdLife(bool thirdLife);

    /**
     * @brief setScore sets the score of the player
     * @param score
     */
    void setScore(int score);

    /**
     * @brief setRunGameLoop sets if the game has to run
     * @param runGameLoop
     */
    void setRunGameLoop(bool runGameLoop);

    /**
     * @brief setShotButtonPressed if the player has pressed the shot button
     * @param shotButtonPressed
     */
    void setShotButtonPressed(bool shotButtonPressed);

    /**
     * @brief setIsTablet sets if the device is a tablet
     * @param isTablet
     */
    void setIsTablet(bool isTablet);

    /**
     * @brief setMusicOn if the player want to swich music on or off
     * @param musicOn
     */
    void setMusicOn(bool musicOn);

    /**
     * @brief setEffectsOn if the player want to switch sound effects on or off
     * @param EffectsOn
     */
    void setEffectsOn(bool EffectsOn);

    /**
     * @brief setNewGame set if a new game starts
     * @param newGame
     */
    void setNewGame(bool newGame);

    /**
     * @brief setGameOver sets if the game is over
     * @param gameOver
     */
    void setGameOver(bool gameOver);

    /**
     * @brief scoresUp adds scorePoints to score property.
     *        uses set score in the process.
     * @param scorePoints
     */
    void scoresUp(int scorePoints);
    /**
     * @brief onSmallEnemyKilled supposed to be called when a smallEnemy is killed by the player,
     *        adds value to score property.
     * @param value the value of the unit wich was killed.
     * @param location location of kill (currently unused).
     */
    void onSmallEnemyKilled (int value, QVector3D location);

    /**
     * @brief onPlayershipHit supposed to be called when playership gets hit.
     * @param value
     */
    void onPlayershipHit();

signals:

    void leftKeyPressedChanged(bool leftKeyPressed);
    void rightKeyPressedChanged(bool rightKeyPressed);
    void firstLifeChanged(bool firstLife);
    void secLifeChanged(bool secLife);
    void thirdLifeChanged(bool thirdLife);
    void scoreChanged(int score);
    void runGameLoopChanged(bool runGameLoop);
    void shotButtonPressedChanged(bool shotButtonPressed);
    void isTabletChanged(bool isTablet);
    void musicOnChanged(bool musicOn);
    void EffectsOnChanged(bool EffectsOn);
    void newGameChanged(bool newGame);
    void gameOverChanged(bool gameOver);

protected:
    //    bool eventFilter(QObject *obj, QEvent *event);
    /**
     * @brief mousePressEvent GUI thread mousePress handler
     *
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief deleteExtraRenderers inherited from base class (new addition),
     * deletes extra renderers wich are not present in base class upon lossage of opengl context.
     * calls GameSceen::deleteSkyBoxRenderer to do so
     *
     * Gets called in base class in GLItem::deleteRenderer wich is a connected slot to the signal aboutToBeDestroyed()
     * from open gl context (connected within GLItem::handleWindowChanged ).
     */
    void deleteExtraRenderers();

    /**
     * @brief keyPressEvent GUI thread keyPress handler
     *        Here we check, which key was pressed and set the flag to true.
     *
     * @param event the actual QKeyEvent
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief keyReleaseEvent GUI thread keyRelease handler
     *        Here we check, if the key is released and set the flag to false;
     * @param event
     */
    void keyReleaseEvent(QKeyEvent *event);

    /**
     * @brief paintUnderQmlScene
     *        Virtual function for painting under a QML scene. This function is called by paintBefore after
     *        calling createGeometries and initializing and binding the renderer.
     *        Overwrite in subclasses for painting geometries in m_points with the renderer.
     */
    virtual void paintUnderQmlScene();

    /**
     * @brief paintUnderQmlScene
     * Virtual function for painting on top of a QML scene. This function is called by paintAfter after
     * calling createGeometries and initializing and binding the renderer.
     * Overwrite in subclasses for painting geometries in m_points with the renderer.
     */
    virtual void paintOnTopOfQmlScene();

    /**
     * @brief setupGeometry puts the geometric data into the arrays (m_Vertices etc.) and sets geometryIsValid flag.
     */
    virtual void setupGeometry();

    /**
     * @brief setupView Setup matrices, lighting and basic GL rendering settings
     * GlItem::setupView sets up a basic view with (0,0,0) in the center of the screen.
     * You may override this function to fit your requirements.
     */
    virtual void setupView(bool clearBuffers);

    //### ExtraRenderer
    void initializeSkyBoxRenderer();
    void deleteSkyBoxRenderer();

    /**
     * @brief setupRenderer Setup matrices, lighting. Does not call glXXX functions
     */
    bool setupSkyBoxRenderer();

    /**
     * @brief doSynchronizeThreads Copy data from GUI-thread to render-thread and vice versa.
     * setup m_cameraTransform
     */
    virtual void doSynchronizeThreads();


private:
    void startNewGame();
    /**
     * @brief m_timer_gameloop the timer of the game
     */
    QTimer * m_timer_gameloop;

    /**
     * @brief m_leftKeyPressed flag for the left key
     */
    bool m_leftKeyPressed;

    /**
     * @brief m_rightKeyPressed flag for the right key
     */
    bool m_rightKeyPressed;

    /**
     * @brief m_spaceKeyPressed flag for the space key
     */
    bool m_spaceKeyPressed;

    /**
     * @brief m_isTablet flag if device is tablet or a mobile phone
     */
    bool m_isTablet;

    /**
     * @brief m_firstLife stores the players first life
     */
    bool m_firstLife;

    /**
     * @brief m_secLife stores the players second life
     */
    bool m_secLife;

    /**
     * @brief m_thirdLife stores the players third life
     */
    bool m_thirdLife;

    /**
     * @brief m_gameOver stores if game is over
     */
    bool m_gameOver;

    /**
     * @brief m_score stores the score of the player
     */
    int m_score;

    /**
     * @brief m_shotButtonPressed stores if shotButton was pressed
     */
    bool m_shotButtonPressed;

    /**
     * @brief m_musicOn stores the value, if music is on
     */
    bool m_musicOn;

    /**
     * @brief m_effectsOn stores the value, if sound effects are on
     */
    bool m_effectsOn;

    /**
     * @brief m_runGameLoop stores the value, if the game loop is running
     */
    bool m_runGameLoop;

    /**
     * @brief m_newGame stores the value if a new game starts
     */
    bool m_newGame;

    //### GLOBAL ROTATION ANGLE
    QMatrix4x4 m_guiThreadCameraMatrix;

    //### INITIAL AND RESET EYE POSITION
    QVector3D m_initialEyePos;

    //### MOUSE EVENT COORDINATES
    QMouseEvent * m_lastMouseEvent; //### A COPY OF THE LAST EVENT, OWNED BY GUI THREAD
    QPoint m_renderedMousePoint; //### OWNED BY RENDER THREAD

    /**
     * @brief m_lastKeyEvent QKeyEvent for the Keys
     */
    QKeyEvent * m_lastKeyEvent;

    //### GEOMETRIC OBJECTS
    GLSkyBox * m_skybox = nullptr;
    GLFrustum * m_frustum = nullptr;
    GLMouseRay * m_mouseRay = nullptr;

    //### For hitbox
    GLCube * m_cube1 = nullptr;
    GLCube * m_cube2 = nullptr;
    GLCube * m_cube3 = nullptr;

    //### GameEngine for spaceinvaders
    GameEngine * m_gameEngine = nullptr;

    //### file locations for shaders
    QString m_skyBoxFragmentShaderFilename;
    QString m_skyBoxVertexShaderFilename;


    //### extra rnderers
    SkyBoxRenderer * m_SkyBoxRenderer = nullptr;

    //Sound
    SoundEngine * m_soundEngine;

    //Gamemusic
    QGameMusicEngine * m_gameMusicEngine;

    //### lighting
    bool m_pointLightEnabled = false;
    QVector3D m_lightDirection = QVector3D(1.0, 1.0, 1.0);
    QVector4D m_lightPos = QVector4D(0.0, 10.0, 0.0, 0.0);
};

#endif // GAMESCEEN_H
