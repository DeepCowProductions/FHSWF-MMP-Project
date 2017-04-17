#include "gamesceen.h"
#include "iostream"

/**
 * @attention A Comment is with ### after // marked and written UPPERCASE.
 */

GameSceen::GameSceen(QQuickItem *parent)
    :GLItem(parent)
{
#ifdef Q_OS_ANDROID
    //### Check if is Tablet or Smartphone
    isTablet();
#endif

    //### SET SHADERS FOR THIS SCEEN
    m_vertexShaderFilename = ":/shaders/vshader.vsh";
    m_fragmentShaderFilename = ":/shaders/fshader.fsh";

    m_skyBoxFragmentShaderFilename = ":/shaders/skyboxfshader.fsh";
    m_skyBoxVertexShaderFilename = ":/shaders/skyboxvshader.vsh";

    setFirstLife(true);
    setSecLife(true);
    setThirdLife(true);
    setShotButtonPressed(false);

    setScore(0);

    //### SET FLAGS FOR PAINTING
    m_activatePaintBeforeQml = true;
    m_activatePaintAfterQml = true;
    m_drawAxes = false;
    m_lightingEnabled = false;
    m_colorArrayEnabled = true;
    m_lightDirection = Spaceinvaders::staticLightDirection;
    
    //### RESET THE VIEW
    resetView();
    
    //### SET ALL BUTTONS
    setAcceptedMouseButtons(Qt::AllButtons);
    
    //### SET THE FOCUS ON THIS SCENE
    setFocus(true);
    //ShaderDebugger::setEnabled(true);
    
    //### OPTIONAL IF THE OS IS ANDROID OR SOMETHING ELSE
#ifdef Q_OS_ANDROID
    m_skybox = new GLSkyBox("MySkyBox",Spaceinvaders::AndroidSkyBoxRadius, GLColorRgba::clWhite);
    m_skybox->setTextureFile(":/starfield");
#else
    m_skybox = new GLSkyBox("MySkyBox",Spaceinvaders::DesktopSkyBoxRadius, GLColorRgba::clWhite);
    m_skybox->setTextureFile(":/starfield");
#endif
    m_lastMouseEvent = NULL;

    //### init gameEngine
    m_gameEngine = new GameEngine(this);

    //### init SoundEngine
    m_soundEngine = new SoundEngine(this);
    m_soundEngine->loadSound(":/gamesound");
    //m_soundEngine->setEnabled(true);
    
    //### INIT TIMERS
    m_timer_gameloop = new QTimer(this);
    m_timer_gameloop->setInterval(Spaceinvaders::GameTicksPerSecond); // set game to run at x ticks per second -> one loop every x seconds
    connect(m_timer_gameloop, &QTimer::timeout,
            this, &GameSceen::onTimer_GameLoopTimeout, Qt::DirectConnection);
    m_timer->setInterval(Spaceinvaders::RenderTicksPerSecond); // draw a frame every x ms with timer in base class
    connect(m_gameEngine, &GameEngine::smallEnemyKilled,this,&GameSceen::onSmallEnemyKilled);

}

GameSceen::~GameSceen()
{
    qDebug() << "GameSceen::destructor call";
    deleteSkyBoxRenderer();

    if(m_skybox)
        delete m_skybox;
    if(m_frustum)
        delete m_frustum;
    if(m_lastMouseEvent)
        delete m_lastMouseEvent;
    if(m_mouseRay)
        delete m_mouseRay;
    if(m_gameEngine)
        delete m_gameEngine;

}

bool GameSceen::isTablet() {
    // Compute screen size
    QDesktopWidget desk;
    QScreen * screen = QGuiApplication::screens().at(0);

    float pixelWidth  = screen->availableGeometry().width();
    float pixelHeight = screen->availableGeometry().height();

    float widthDPI = screen->physicalDotsPerInchX();
    float heightDPI = screen->physicalDotsPerInchY();

    float widthInches = pixelWidth/widthDPI;
    float heightInches = pixelHeight/heightDPI;

    double diagonalInches = qSqrt((widthInches * widthInches) + (heightInches * heightInches));

    qDebug() << "Screen Size: " + QString::number(diagonalInches);

    bool isTablet;
    // Tablet devices should have a screen size greater than 6 inches
    if(diagonalInches > 6) {
        isTablet = true;
        setIsTablet(true);
    }
    else {
        isTablet = false;
        setIsTablet(false);
    }

    /*float width = screen->physicalSize().width();
    float height = screen->physicalSize().height();

    double diagonalInches = qSqrt((width*width)+(height*height));
    qDebug() << "Screen Size: " + QString::number(diagonalInches/25.4);

    bool isTablet;
    // Tablet devices should have a screen size greater than 6 inches
    if(diagonalInches > 6) {
        isTablet = true;
        setIsTablet(true);
    }
    else {
        isTablet = false;
        setIsTablet(false);
    }*/
    return isTablet;
}


void GameSceen::resetView()
{
    m_guiThreadCameraMatrix.setToIdentity();
#ifdef Q_OS_ANDROID
    m_eye = Spaceinvaders::AndroidViewVector.x() * Spaceinvaders::ViewDirection;
    m_near = Spaceinvaders::AndroidViewVector.y();
    m_far = Spaceinvaders::AndroidViewVector.z();
#else
    m_eye = Spaceinvaders::DesktopViewVector.x() * Spaceinvaders::ViewDirection;
    m_near = Spaceinvaders::DesktopViewVector.y();
    m_far = Spaceinvaders::DesktopViewVector.z();
#endif
    m_spaceKeyPressed = false;
    m_leftKeyPressed = false;
    m_rightKeyPressed = false;
}

void GameSceen::onTimer_GameLoopTimeout()
{
    qDebug() << "timer game loop timer time out";
    gameLoopTimeout();
}

void GameSceen::gameLoopTimeout()
{
    //### CHECK IF IS LANDSCAPE OR PORTRAIT(Tablet or Smartphone) AND MOVEMENT IF KEY PRESSED
#ifdef Q_OS_ANDROID
    if(!orientation())
        m_eye = 35.0 * -QVector3D(0.0,-0.5,1.0);
    else if(orientation())
        m_eye = 80.0 * -QVector3D(0.0,-0.5,1.0);
    if (m_leftKeyPressed) {
        gameEngine()->playership()->translate(QVector3D(1.0,0.0,0.0));
    }
    if (m_rightKeyPressed) {
        gameEngine()->playership()->translate(QVector3D(-1.0,0.0,0.0));
    }

    //## for testing shoots everytime it can
    /*if (etes){
        gameEngine()->shootWithPlayerShip();
        etes = false;
    }*/


#else
    //qDebug() << m_leftKeyPressed;

    //## for testing shoots everytime it can
    /*if (etes){
        gameEngine()->shootWithPlayerShip();
        etes = false;
    }*/


    if (m_leftKeyPressed) {
        //### nur zum umschaune  und debuggen
        //        m_guiThreadCameraMatrix.rotate(1.0, v_X);
        gameEngine()->playership()->translate(QVector3D(0.8,0.0,0.0));
        //        m_spaceship->moveVirtual(QVector3D(0.8,0.0,0.0));
    }
    if (m_rightKeyPressed) {
        //        m_spaceship->moveVirtual(QVector3D(-0.8,0.0,0.0));
        gameEngine()->playership()->translate(QVector3D(-0.8,0.0,0.0));
    }
#endif

    //### fehlt noch das controll
    if (m_spaceKeyPressed || m_shotButtonPressed) {
        gameEngine()->shootWithPlayerShip();
        //scoresUp(10);
    }


    //### move all NPC entities with this call
    gameEngine()->processEntities();

    //### lastly call base class definition for window update

}

void GameSceen::timerTimeout()
{
    GLItem::timerTimeout();
}

void GameSceen::deleteExtraRenderers()
{
    m_timer_gameloop->stop();
    deleteSkyBoxRenderer();
}

void GameSceen::setLeftKeyPressed(bool leftKeyPressed)
{
    if (m_leftKeyPressed == leftKeyPressed)
        return;

    m_leftKeyPressed = leftKeyPressed;
    emit leftKeyPressedChanged(leftKeyPressed);
}

void GameSceen::setRightKeyPressed(bool rightKeyPressed)
{
    if (m_rightKeyPressed == rightKeyPressed)
        return;

    m_rightKeyPressed = rightKeyPressed;
    emit rightKeyPressedChanged(rightKeyPressed);
}

void GameSceen::setFirstLife(bool firstLife)
{
    if (m_firstLife == firstLife)
        return;

    m_firstLife = firstLife;
    emit firstLifeChanged(firstLife);
}

void GameSceen::setSecLife(bool secLife)
{
    if (m_secLife == secLife)
        return;

    m_secLife = secLife;
    emit secLifeChanged(secLife);
}

void GameSceen::setThirdLife(bool thirdLife)
{
    if (m_thirdLife == thirdLife)
        return;

    m_thirdLife = thirdLife;
    emit thirdLifeChanged(thirdLife);
}

void GameSceen::setScore(int score)
{
    if (m_score == score)
        return;

    m_score = score;
    emit scoreChanged(score);
}

void GameSceen::setRunGameLoop(bool runGameLoop)
{
    qDebug() << m_timer_gameloop->isActive();
    if (m_runGameLoop == runGameLoop)
        return;

    m_runGameLoop = runGameLoop;

    if (m_runGameLoop)
        m_timer_gameloop->start();
    else
        m_timer_gameloop->stop();
    emit runGameLoopChanged(runGameLoop);
    qDebug() << m_timer_gameloop->isActive();
}

void GameSceen::setShotButtonPressed(bool shotButtonPressed)
{
    if (m_shotButtonPressed == shotButtonPressed)
        return;

    m_shotButtonPressed = shotButtonPressed;
    emit shotButtonPressedChanged(shotButtonPressed);
}

void GameSceen::setIsTablet(bool isTablet)
{
    if (m_isTablet == isTablet)
        return;

    m_isTablet = isTablet;
    emit isTabletChanged(isTablet);
}

void GameSceen::setMusicOn(bool musicOn)
{
    if (m_musicOn == musicOn)
        return;


    m_musicOn = musicOn;
    emit musicOnChanged(musicOn);
}


void GameSceen::mousePressEvent(QMouseEvent *event)
{
    (void)event;
}

void GameSceen::keyPressEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()){
        QString s = QString("My PRESS key is %1. The counter is %2").arg(event->text(), QString::number(keyCounter));
        qDebug() << s;
        keyCounter++;
        
        switch (event->key()) {
        // left and a
        case Qt::Key_Left: case 0x41:
            m_leftKeyPressed = true;
            break;
            // right and d
        case Qt::Key_Right: case 0x44 :
            m_rightKeyPressed = true;
            break;
        case Qt::Key_Space:
            m_spaceKeyPressed = true;
            break;
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

        switch (event->key()) {
        case Qt::Key_Left: case 0x41:
            m_leftKeyPressed = false;
            break;
        case Qt::Key_Right: case 0x44:
            m_rightKeyPressed = false;
            break;
        case Qt::Key_Space:
            m_spaceKeyPressed = false;
            break;
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
    //### other
    m_SkyBoxRenderer->bind();

    m_skybox->draw(m_SkyBoxRenderer);

    m_SkyBoxRenderer->release();

    //### entities
    m_renderer->bind();

    //    m_spaceship->draw(renderer());
    m_gameEngine->drawEntities(renderer());

    m_renderer->release();

}

void GameSceen::paintOnTopOfQmlScene()
{


}

void GameSceen::setupGeometry()
{
    //createAxes(6.0);
    m_geometryIsValid = true;
    //    m_spaceship->loadWavefrontFile(":/spaceship2",NULL,NULL);
    m_gameEngine->playership()->glModel()->loadWavefrontFile(":/spaceship2",NULL,NULL);
    //    qDebug() << "timer is active" << m_timer_gameloop->isActive();
}

void GameSceen::setupView(bool clearBuffers)
{
    // erstmal nur provisorisch hier
    if(!m_SkyBoxRenderer)
        initializeSkyBoxRenderer();

    if(!setupSkyBoxRenderer())
        return;
    GLItem::setupView(clearBuffers);
}

bool GameSceen::setupSkyBoxRenderer()
{
    qreal ratio = window()->devicePixelRatio();
    m_viewportW = int(ratio * width());
    m_viewportH = int(ratio * height());
    m_SkyBoxRenderer->setViewport(m_viewportX, m_viewportY, m_viewportW, m_viewportH);

    m_aspect = (double)m_viewportW / (double)m_viewportH;
    if(! m_orthoMode ){
        m_SkyBoxRenderer->setPerspective(m_fovy,
                                         m_aspect,
                                         m_near,
                                         m_far);
    }
    else {
        m_SkyBoxRenderer->setOrtho(-m_orthoRange * m_aspect, m_orthoRange * m_aspect,
                                   -m_orthoRange, m_orthoRange, 0.1, 100.0); // for debugging
    }
    m_SkyBoxRenderer->setLookAt(m_eye, //eye
                                m_center, //center
                                m_up);//up
    //setup light before turning
    m_SkyBoxRenderer->setLightDirection(m_lightDirection);
    m_SkyBoxRenderer->setLightingEnabled(true);
    //now turn
    m_SkyBoxRenderer->transform(m_cameraTransform);
    return true;
}


void GameSceen::initializeSkyBoxRenderer()
{
    qDebug() <<"GlItem::initializeRenderer called.";
    if(!m_SkyBoxRenderer)
        m_SkyBoxRenderer = new SkyBoxRenderer(NULL, m_skyBoxVertexShaderFilename, m_skyBoxFragmentShaderFilename);

}

void GameSceen::deleteSkyBoxRenderer()
{
    qDebug() <<"GlItem::deleteSkyBoxRenderer() called.";
    if(m_SkyBoxRenderer)
    {
        delete m_SkyBoxRenderer;
        m_SkyBoxRenderer = NULL;
    }
}


void GameSceen::doSynchronizeThreads()
{
    m_cameraTransform = m_guiThreadCameraMatrix;
    gameEngine()->snycEntities();
    
    
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

void GameSceen::scoresUp(int scorePoints)
{
    setScore(score() + scorePoints);
}

void GameSceen::onSmallEnemyKilled(int value, QVector3D location)
{
    scoresUp(value);
}

GameEngine *GameSceen::gameEngine() const
{
    return m_gameEngine;
}

bool GameSceen::shotButtonPressed() const
{
    return m_shotButtonPressed;
}
