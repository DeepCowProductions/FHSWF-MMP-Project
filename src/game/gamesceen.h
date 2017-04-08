#ifndef GAMESCEEN_H
#define GAMESCEEN_H

#include "../glcore/glitem.h"
#include "../globjects/glspaceship.h"
#include "../globjects/glfrustum.h"
#include "../globjects/glmouseray.h"
#include "../globjects/glskybox.h"
#include "../glcore/shaderdebugger.h"
#include "../glcore/skyboxrenderer.h"
#include "gameengine.h"
#include <QDesktopWidget>
#include <QScreen>
#include <QGuiApplication>
#include <QQuickWindow>
#include <QShortcut>
#include <QtMath>

/**
 * @brief The GameSceen class
 *
 * @attention A Comment is with ### after // marked and written UPPERCASE.
 *
 * @author Kuhmichel(1004128) and Grabelus(10044563)
 */
class GameSceen : public GLItem
{
    Q_OBJECT
    //### PROPERTIES OF THE SPACEINVADERS.QML FOR INTERACTING
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
     * The Constructor where we set all at the beginning of the Game.
     *
     * @param parent
     */
    GameSceen(QQuickItem *parent = 0);
    ~GameSceen();

    /**
     * @brief isTablet for use in this class to detect, if is a Tablet or Smartphone(is used for QML)
     * @return
     */
    bool isTablet();

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
     * @brief orientation returns if the smartphone is in portrait or landscape mode
     *
     * @return boolean value
     */

    bool firstLife() const {   return m_firstLife;    }

    bool secLife() const {   return m_secLife;    }

    bool thirdLife() const {   return m_thirdLife;    }

    int score() const {   return m_score;    }

    bool runGameLoop() const {  return m_runGameLoop;   }

    GameEngine *gameEngine() const;

    bool shotButtonPressed() const
    {
        return m_shotButtonPressed;
    }

public slots:
    /**
     * @brief resetView slot for reseting the view.
     *        Which is only at begin in use, at moment.
     *        Other moments for use, maybe implemented later.
     */
    void resetView();

    /**
     * @brief gameloopTimeout controlls timedependend operations, seperate from updateWindow().
     * unused.
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
     * @brief setOrientation checks if the orientation has changed,
     *        if yes emit a signal.
     *
     * @param orientation bool
     */

    void setFirstLife(bool firstLife);

    void setSecLife(bool secLife);

    void setThirdLife(bool thirdLife);

    void setScore(int score);

    void setRunGameLoop(bool runGameLoop);


    void setShotButtonPressed(bool shotButtonPressed)
    {
        if (m_shotButtonPressed == shotButtonPressed)
            return;

        m_shotButtonPressed = shotButtonPressed;
        emit shotButtonPressedChanged(shotButtonPressed);
    }

    void setIsTablet(bool isTablet)
    {
        if (m_isTablet == isTablet)
            return;

        m_isTablet = isTablet;
        emit isTabletChanged(isTablet);
    }

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



    bool m_runGameLoop;

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
     * @brief m_orientation flag for the orentation of the mobile phone
     */
    bool m_isTablet;
    bool m_firstLife;
    bool m_secLife;
    bool m_thirdLife;
    int m_score;
    bool m_shotButtonPressed;

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

    //### GameEngine for spaceinvaders
    GameEngine * m_gameEngine = nullptr;
    /**
     * @brief m_spaceship the spaceship of the player
     */
    GLSpaceShip * m_spaceship = nullptr;
    bool etes = true;

    //### file locations for shaders
    QString m_skyBoxFragmentShaderFilename;
    QString m_skyBoxVertexShaderFilename;


    //### extra rnderers
    SkyBoxRenderer * m_SkyBoxRenderer = nullptr;


    //### lighting ?
    bool m_pointLightEnabled = false;
    QVector3D m_lightDirection = QVector3D(1.0, 1.0, 1.0);
    QVector4D m_lightPos = QVector4D(0.0, 10.0, 0.0, 0.0);

};

#endif // GAMESCEEN_H
