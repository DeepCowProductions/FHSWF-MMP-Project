#include "gamesceen.h"
#include <QQuickWindow>
#include <QShortcut>

/**
 * @attention A Comment is with ### after // marked and written UPPERCASE.
 */

GameSceen::GameSceen(QQuickItem *parent)
    :GLItem(parent)
{
    //### SET SHADERS FOR THIS SCEEN
    m_vertexShaderFilename = ":/shaders/vshader.vsh";
    m_fragmentShaderFilename = ":/shaders/fshader.fsh";

    //### SET FLAGS FOR PAINTING
    m_activatePaintBeforeQml = true;
    m_activatePaintAfterQml = true;
    m_drawAxes = false;
    m_lightingEnabled = true;
    m_colorArrayEnabled = true;

    //### RESET THE VIEW
    resetView();

    //### SET ALL BUTTONS
    setAcceptedMouseButtons(Qt::AllButtons);

    //### SET THE FOCUS ON THIS SCENE
    setFocus(true);
    //ShaderDebugger::setEnabled(true);

    //### SET UP TESTOBJECTS... [...]
    m_cube = new GLCube("MyCube");
    m_sphere = new GLSphere("MySphere",10.0, GLColorRgba::clWhite);
    m_sphere->setTextureFile(":/textures/stars.jpg");
    //    m_frustum = new GLFrustum("Frustum", GLColorRgba::clWhite);
    //    m_mouseRay = new GLMouseRay("MouseRay");
    m_lastMouseEvent = NULL;

    //### INIT SPACESHIP
    m_spaceship = new GLSpaceShip("3D Spaceship");
    m_spaceship->setTextureFile(":/spaceshipTex"); // use alias

    //### INIT TIMER
    m_timer_gameloop = new QTimer(this);

    //### OPTIONAL IF THE OS IS ANDROID OR SOMETHING ELSE
#ifdef Q_OS_ANDROID
    m_timer_gameloop->setInterval(1); // set game to run at 1 ticks per second
    connect(m_timer_gameloop, &QTimer::timeout,
            this, &GameSceen::gameloopTimeout, Qt::DirectConnection);
#else
    m_timer_gameloop->setInterval(10); // set game to run at 20 ticks per second
    connect(m_timer_gameloop, &QTimer::timeout,
            this, &GameSceen::gameloopTimeout, Qt::DirectConnection);
#endif

}

GameSceen::~GameSceen()
{
    m_timer_gameloop->stop();

    if(m_cube)
        delete m_cube;
    if(m_sphere)
        delete m_sphere;
    if(m_frustum)
        delete m_frustum;
    if(m_lastMouseEvent)
        delete m_lastMouseEvent;
    if(m_mouseRay)
        delete m_mouseRay;

}


void GameSceen::resetView()
{
    m_guiThreadCameraMatrix.setToIdentity();
#ifdef Q_OS_ANDROID
    m_eye = 80.0 * -QVector3D(0.0,-0.5,1.0);
    m_near = 10.0;
    m_far = 90.0;
#else
    m_eye = 40.0 * -QVector3D(0.0,-0.5,1.0);
    m_near = 10.0;
    m_far = 50.0;
#endif
    m_spaceKeyPressed = false;
    m_leftKeyPressed = false;
    m_rightKeyPressed = false;
}

void GameSceen::mousePressEvent(QMouseEvent *event)
{
    (void)event;
}

//### ????

//void GameSceen::keyPressEvent(QKeyEvent *event)
//{
//    switch (event->key()) {
//    case Qt::Key_Left :
//        m_leftKeyPressed = true;
//        break;

//    case Qt::Key_Right:
//        m_rightKeypresed = true;
//        break;
//        // more...

//    default:
//        GLItem::keyPressEvent(event);
//        break;
//    }

//}

//void GameSceen::keyReleaseEvent(QKeyEvent *event)
//{
//    switch (event->key()) {
//    case Qt::Key_Left :
//        m_leftKeyPressed = false;
//        break;

//    case Qt::Key_Right:
//        m_rightKeypresed = false;
//        break;
//        // more...

//    default:
//        GLItem::keyPressEvent(event);
//        break;
//    }

//}

void GameSceen::keyPressEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()){
        QString s = QString("My PRESS key is %1. The counter is %2").arg(event->text(), QString::number(keyCounter));
        qDebug() << s;
        keyCounter++;

        //### KP bei QT ging das normale gruppieren von CASES nicht iwie,
        //### wenn du es hinkriegst, dann wäre es cool :)

        switch (event->key()) {
        // left and a
        case Qt::Key_Left: case 0x41:
            m_leftKeyPressed = true;
            break;
        // right and d
        case Qt::Key_Right: case 0x44 :
            m_rightKeyPressed = true;
            break;
            // more...

        default:
            GLItem::keyPressEvent(event);
            break;
        }


    }
}

void GameSceen::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()){
        QString s = QString("My RELEASE key is %1. The counter is %2").arg(event->text(), QString::number(keyCounter));
        qDebug() << s;
        keyCounter--;

        //### siehe KeyPressEvent kommentar
        switch (event->key()) {
        case Qt::Key_Left : case 0x41:
            m_leftKeyPressed = false;
            break;

        case Qt::Key_Right: case 0x44:
            m_rightKeyPressed = false;
            break;
            // more...

        default:
            GLItem::keyPressEvent(event);
            break;
        }


    }
}

//bool GameSceen::eventFilter(QObject *obj, QEvent *event)
//{
//    if (event->type() == QEvent::KeyPress)
//    {
//        this->keyPressEvent(dynamic_cast<QKeyEvent*>(event));
//        return true;
//    }
//    else if (event->type() == QEvent::KeyRelease)
//    {
//        this->keyReleaseEvent(dynamic_cast<QKeyEvent*>(event));
//        return  true;
//    }
//    else
//    {
//        return QObject::eventFilter(obj, event);
//    }
//}



void GameSceen::paintUnderQmlScene()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameSceen::paintOnTopOfQmlScene()
{
    m_sphere->draw(renderer());
    m_spaceship->draw(renderer());
}

void GameSceen::setupGeometry()
{
    //createAxes(6.0);
    m_geometryIsValid = true;
    m_spaceship->loadWavefrontFile(":/spaceship2",NULL,NULL);
    m_timer_gameloop->start();
}


void GameSceen::doSynchronizeThreads()
{
    m_cameraTransform = m_guiThreadCameraMatrix;

    //### CHECK IF IS LANDSCAPE OR PORTRAIT AND MOVEMENT IF KEY PRESSED
#ifdef Q_OS_ANDROID
    if(!orientation())
        m_eye = 35.0 * -QVector3D(0.0,-0.5,1.0);
    else if(orientation())
        m_eye = 80.0 * -QVector3D(0.0,-0.5,1.0);
    if (m_leftKeyPressed) {
        m_spaceship->move(QVector3D(1.0,0.0,0.0));
    }
    if (m_rightKeyPressed) {
        m_spaceship->move(QVector3D(-1.0,0.0,0.0));
    }
#else
    //qDebug() << m_leftKeyPressed;
    if (m_leftKeyPressed) {
        m_spaceship->moveVirtual(QVector3D(0.1,0.0,0.0));
//        m_spaceship->move(QVector3D(0.8,0.0,0.0));
    }
    if (m_rightKeyPressed) {
        m_spaceship->moveVirtual(QVector3D(-0.1,0.0,0.0));
//        m_spaceship->move(QVector3D(-0.8,0.0,0.0));
    }
#endif


    if(m_lastMouseEvent && !m_lastMouseEvent->isAccepted()) //last mouse event still pending
    {
        switch (m_lastMouseEvent->type()){
        case QEvent::MouseButtonPress:
            m_frustum->invalidateSurface();
            m_mouseRay->setMousePosition(m_lastMouseEvent->pos());
            break;
        case QEvent::MouseMove:
            break;
        case QEvent::MouseButtonRelease:
            break;
        default: qDebug() << "MyGLItem::doSynchronizeThreads(): Unknown mouse event";
        }
        m_lastMouseEvent->setAccepted(true);
    }
}

void GameSceen::gameloopTimeout()
{
    // events...
    //    if (m_leftKeyPressed)
    //        m_sphere->move(QVector3D(0.1,0.0,0.0));
    //    if (m_rightKeypresed)
    //        m_sphere->move(QVector3D(-0.1,0.0,0.0));


    // uppdate window to draw current changes
    // can be called seperatly as well -> framerate timer
    //    GLItem::timerTimeout(); // base class
    if (window())
        window()->update();
    update();
}
