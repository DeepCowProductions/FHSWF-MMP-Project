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
    m_skybox = new GLSkyBox("MySkyBox",Spaceinvaders::DesktopSkyBoxRadius, GLColorRgba::clWhite);
    m_skybox->setTextureFile(":/starfield");
    m_lastMouseEvent = NULL;

    //### init gameEngine
    m_gameEngine = new GameEngine(this);

    //### init SoundEngine
    //m_soundEngine = new SoundEngine(this);
    //m_soundEngine->loadSound(":/gamesound");
    //m_soundEngine->setEnabled(true);

    //### init GameMusicEngine
    m_gameMusicEngine = new QGameMusicEngine(this);
#ifdef Q_OS_ANDROID
    m_gameMusicEngine->loadGameMusic("assets:/sounds/GameSound.mp3");
#else
    m_gameMusicEngine->loadGameMusic("../FHSWF-MMP-Project/sounds/GameSound.mp3");
#endif
    //### INIT TIMER
    m_timer_gameloop = new QTimer(this);
    m_timer_gameloop->setInterval(Spaceinvaders::GameTickCooldownInMillSec); // set game to run at x ticks per second -> one loop every x seconds
    connect(m_timer_gameloop, &QTimer::timeout,
            this, &GameSceen::onTimer_GameLoopTimeout, Qt::DirectConnection);
    m_timer->setInterval(Spaceinvaders::RenderTickCooldownInMillSec); // draw a frame every x ms with timer in base class
    connect(m_gameEngine, &GameEngine::smallEnemyKilled,this,&GameSceen::onSmallEnemyKilled);
    connect(m_gameEngine, &GameEngine::playershipHit, this, &GameSceen::onPlayershipHit);

    //### dislay ship hitbox
    m_cube1 = new GLCube("c1",QVector3D(3.5,0.7,-4.0), QVector3D(-3.5,0.0,-7.0));
    m_cube2 = new GLCube("c1",QVector3D(1.2,1.0,3.5), QVector3D(-1.2,-0.2,-6.5));
    m_cube3 = new GLCube("c1",QVector3D(2.5,0.9,2.5), QVector3D(-2.5,0.30,-1.0));

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
    if(m_gameMusicEngine)
        delete m_gameMusicEngine;

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
    m_shotButtonPressed = false;
    setFirstLife(true);
    setSecLife(true);
    setThirdLife(true);
    setScore(0);
    m_gameOver = false;
    m_newGame = false;
    m_musicOn = musicOn();
}

void GameSceen::onTimer_GameLoopTimeout()
{
    //    qDebug() << "timer game loop timer time out";
    gameLoopTimeout();
}

void GameSceen::gameLoopTimeout()
{
    //### MOVE IF KEY PRESSED
    if (m_leftKeyPressed) {
        //### nur zum umschaune  und debuggen
//        m_guiThreadCameraMatrix.rotate(1.0, v_X);
        gameEngine()->playership()->tryMove(QVector3D(Spaceinvaders::playerShipMovementSpeed,0.0,0.0));
    }
    if (m_rightKeyPressed) {
//        m_guiThreadCameraMatrix.rotate(1.0, v_Y);
        gameEngine()->playership()->tryMove(QVector3D(-Spaceinvaders::playerShipMovementSpeed,0.0,0.0));
    }
    //### fehlt noch das controll
    if (m_spaceKeyPressed || m_shotButtonPressed) {
        gameEngine()->shootWithPlayerShip();
        //scoresUp(10);
    }

    //### move all NPC entities with this call
    gameEngine()->processEntities();

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
    m_gameMusicEngine->startGameMusic(musicOn);
    if(musicOn)
        m_gameMusicEngine->playGameMusic();
    else
        m_gameMusicEngine->stopGameMusic();
    emit musicOnChanged(musicOn);
}

void GameSceen::setEffectsOn(bool EffectsOn)
{
    if (m_effectsOn == EffectsOn)
        return;

    m_effectsOn = EffectsOn;
    m_gameEngine->setEffectsOn(EffectsOn);
    emit EffectsOnChanged(EffectsOn);
}

void GameSceen::setNewGame(bool newGame)
{
    if (m_newGame == newGame)
        return;

    m_newGame = newGame;
    if(newGame)
        startNewGame();
    emit newGameChanged(newGame);
}

void GameSceen::setGameOver(bool gameOver)
{
    if (m_gameOver == gameOver)
        return;

    m_gameOver = gameOver;
    emit gameOverChanged(gameOver);
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

    m_gameEngine->drawEntities(renderer());
    //draw static hitbox
//    m_cube1->draw(renderer());
//    m_cube2->draw(renderer());
//    m_cube3->draw(renderer());

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
    m_gameEngine->enemy()->loadWavefrontFile(":/enemy", NULL, NULL);
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
    
//    if(m_lastMouseEvent && !m_lastMouseEvent->isAccepted()) //last mouse event still pending
//    {
//        switch (m_lastMouseEvent->type()){
//        case QEvent::MouseButtonPress:
//            m_frustum->invalidateSurface();
//            m_mouseRay->setMousePosition(m_lastMouseEvent->pos());
//            break;
//        case QEvent::MouseMove:
//            break;
//        case QEvent::MouseButtonRelease:
//            break;
//        default: qDebug() << "MyGLItem::doSynchronizeThreads(): Unknown mouse event";
//        }
//        m_lastMouseEvent->setAccepted(true);
//    }
}

void GameSceen::startNewGame()
{
#ifdef Q_OS_ANDROID
    //### Check if is Tablet or Smartphone
    isTablet();
#endif
    m_gameEngine = new GameEngine(this);
    m_gameEngine->setSoundEngineEnabled(m_effectsOn);
    setupGeometry();
    //### RESET THE VIEW
    resetView();

    //### SET ALL BUTTONS
    setAcceptedMouseButtons(Qt::AllButtons);

    //### SET THE FOCUS ON THIS SCENE
    setFocus(true);
    m_lastMouseEvent = NULL;

    m_timer_gameloop = new QTimer(this);
    m_timer_gameloop->setInterval(Spaceinvaders::GameTickCooldownInMillSec); // set game to run at x ticks per second -> one loop every x seconds
    connect(m_timer_gameloop, &QTimer::timeout,
            this, &GameSceen::onTimer_GameLoopTimeout, Qt::DirectConnection);
    m_timer->setInterval(Spaceinvaders::RenderTickCooldownInMillSec); // draw a frame every x ms with timer in base class
    connect(m_gameEngine, &GameEngine::smallEnemyKilled,this,&GameSceen::onSmallEnemyKilled);
    connect(m_gameEngine, &GameEngine::playershipHit, this, &GameSceen::onPlayershipHit);

    //### dislay ship hitbox
//    m_cube1 = new GLCube("c1",QVector3D(5.8,0.7,-7.0), QVector3D(-5.8,0.0,-12.0));
//    m_cube2 = new GLCube("c1",QVector3D(1.5,1.5,7.8), QVector3D(-1.5,-1.0,-10.78));
//    m_cube3 = new GLCube("c1",QVector3D(3.0,1.2,6.2), QVector3D(-3,0.25,0.5));

//    //### entities
//    m_renderer->bind();

//    //    m_spaceship->draw(renderer());
//    m_gameEngine->drawEntities(renderer());
//    m_cube1->draw(renderer());
//    m_cube2->draw(renderer());
//    m_cube3->draw(renderer());

//    m_renderer->release();
}

void GameSceen::scoresUp(int scorePoints)
{
    setScore(score() + scorePoints);
}

void GameSceen::onSmallEnemyKilled(int value, QVector3D location)
{
    scoresUp(value);
}

void GameSceen::onPlayershipHit()
{
    if(m_firstLife) {
        setFirstLife(false);
        qDebug() << "GameSceen::onPlayershipHit: Only 2 lifes left";
    }
    else if(m_secLife) {
        setSecLife(false);
        qDebug() << "GameSceen::onPlayershipHit: Only 1 life left";
    }
    else if(m_thirdLife) {
        setThirdLife(false);
        qDebug() << "GameSceen::onPlayershipHit: GAMEOVER";
        setRunGameLoop(false);
        setGameOver(true);
        m_gameEngine->gameOver();
    }
    qDebug() << "playership hit!";
}

GameEngine *GameSceen::gameEngine() const
{
    return m_gameEngine;
}

bool GameSceen::shotButtonPressed() const
{
    return m_shotButtonPressed;
}
