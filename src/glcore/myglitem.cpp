#include "myglitem.h"
#include "glpoint.h"
#include "glcolorrgba.h"
#include "shaderdebugger.h"

MyGLItem::MyGLItem(QQuickItem *parent)
    :GLItem(parent)
{
    m_vertexShaderFilename = ":/shaders/vshader.vsh";
    m_fragmentShaderFilename = ":/shaders/fshader.fsh";

    m_activatePaintBeforeQml = true;
    m_activatePaintAfterQml = false;
    m_drawAxes = true;
    m_firstTriangleIndex = 0;
    m_lastTriangleIndex = 0;
    m_lightingEnabled = true;
    m_colorArrayEnabled = false;
    
    resetView();

    m_mainlopptimer = new QTimer(this);
    m_mainlopptimer->setInterval(50);
    connect(m_mainlopptimer, &QTimer::timeout,
            this, &MyGLItem::mainloopTimeout, Qt::DirectConnection);

    //ShaderDebugger::setEnabled(true);

    m_cube = new GLCube("MyCube");
    m_sphere = new GLSphere("MySphere",2.0, GLColorRgba::clWhite);
    m_sphere->setTextureFile(":/textures/earthmap1024x512.jpg");
    m_frustum = new GLFrustum("Frustum", GLColorRgba::clWhite);
    m_mouseRay = new GLMouseRay("MouseRay");
    setAcceptedMouseButtons(Qt::AllButtons);
    m_lastMouseEvent = NULL;
    m_spaceship = new GLSpaceShip("3D Spaceship");
    m_spaceship->setTextureFile(":/spaceshipTex"); // use alias

    m_soundEngine = new SoundEngine(this);
}

MyGLItem::~MyGLItem()
{
  if(m_cube)
      delete m_cube;
  if(m_sphere)
      delete m_sphere;
  if(m_frustum)
      delete m_frustum;
  if(m_lastMouseEvent)
      delete m_lastMouseEvent;
//  if(m_mouseRay)
//      delete m_mouseRay;
  if(m_spaceship)
      delete m_spaceship;
}

void MyGLItem::createCube(const QVector3D &lbb, const QVector3D &rtf)
{
    m_firstCubePoint = m_points.size();
    m_firstCubeIndex = m_indices.size();
    //corners
    QVector3D v0 = lbb;
    QVector3D vX = QVector3D(rtf.x(), lbb.y(), lbb.z());
    QVector3D vY = QVector3D(lbb.x(), rtf.y(), lbb.z());
    QVector3D vZ = QVector3D(lbb.x(), lbb.y(), rtf.z());
    QVector3D vXY = QVector3D(rtf.x(), rtf.y(), lbb.z());
    QVector3D vXZ = QVector3D(rtf.x(), lbb.y(), rtf.z());
    QVector3D vYZ = QVector3D(lbb.x(), rtf.y(), rtf.z());
    QVector3D vXYZ = rtf;

    //Left
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vY, -v_X, v_X, GLColorRgba::clMagenta));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v0, -v_X, v_Zero, GLColorRgba::clMagenta));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vYZ, -v_X, v_XY, GLColorRgba::clMagenta));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vZ, -v_X, v_Y, GLColorRgba::clMagenta));
    m_indices.append(m_points.size()); //One degenerate triangle, we have to turn around the corner

    //Front
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vZ, v_Z, v_Zero, GLColorRgba::clRed));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vXZ, v_Z, v_X, GLColorRgba::clRed));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vYZ, v_Z, v_Y, GLColorRgba::clRed));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vXYZ, v_Z, v_XY, GLColorRgba::clRed));

    //Top
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vXYZ, v_Y, v_XY, GLColorRgba::clYellow));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vYZ, v_Y, v_Y, GLColorRgba::clYellow));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vXY, v_Y, v_X, GLColorRgba::clYellow));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vY, v_Y, v_Zero, GLColorRgba::clYellow));

    //Back
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vY, -v_Z, v_Y, GLColorRgba::clGreen));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vXY, -v_Z, v_XY, GLColorRgba::clGreen));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v0, -v_Z, v_Zero, GLColorRgba::clGreen));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vX, -v_Z, v_X, GLColorRgba::clGreen));

    //Bottom
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vX, -v_Y, v_Y, GLColorRgba::clBlue));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v0, -v_Y, v_Zero, GLColorRgba::clBlue));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vXZ, -v_Y, v_XY, GLColorRgba::clBlue));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vZ, -v_Y, v_X, GLColorRgba::clBlue));
    m_indices.append(m_points.size()); //One degenerate triangle, we have to turn around the corner

    //Right
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vXZ, v_X, v_X, GLColorRgba::clCyan));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vX, v_X, v_Zero, GLColorRgba::clCyan));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vXYZ, v_X, v_XY, GLColorRgba::clCyan));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(vXY, v_X, v_Y, GLColorRgba::clCyan));

    m_lastCubeIndex = m_indices.size() - 1;
    m_lastCubePoint = m_points.size() - 1;
}


void MyGLItem::createVisibleNormals()
{
    m_firstNormalPoint = m_points.size();

    for(int i = 0; i < m_firstNormalPoint; i++)
    {
        m_points.append(GLPoint(m_points[i].vertex(),
                                m_points[i].normal(),
                                m_points[i].texCoord(),
                                cl_White));
        m_points.append(GLPoint(m_points[i].vertex() + m_points[i].normal(),
                                m_points[i].normal(),
                                m_points[i].texCoord(),
                                cl_White));
    }

    m_lastNormalPoint = m_points.size() - 1;
}

void MyGLItem::drawNormals()
{
    renderer()->setLightingEnabled(false);
    renderer()->setColorArrayEnabled(true);
    renderer()->setTextureEnabled(false);

    //enable required arrays
    int stride = sizeof(GLPoint);
    renderer()->activateAttributeArray(GLESRenderer::VERTEX_LOCATION,
                                     m_points[0].vertexPointer(), stride);
    renderer()->activateAttributeArray(GLESRenderer::NORMAL_LOCATION,
                                        m_points[0].normalPointer(), stride);
    renderer()->activateAttributeArray(GLESRenderer::TEXCOORD_LOCATION,
                 m_points[0].texCoordPointer(), stride);
    renderer()->activateAttributeArray(GLESRenderer::COLOR_LOCATION,
                 m_points[0].colorPointer(), stride);

    glDrawArrays(GL_LINES, m_firstNormalPoint, m_lastNormalPoint - m_firstNormalPoint +1);

    renderer()->disableAttributeArrays();
    renderer()->setLightingEnabled(m_lightingEnabled);
}


void MyGLItem::resetView()
{
    m_guiThreadCameraMatrix.setToIdentity();
    m_rotateX = false;
    m_rotateY = false;
    m_rotateZ = false;
    setRotationX(0.0);
    setRotationY(0.0);
    setRotationZ(0.0);
    m_eye = 10.0 * v_XYZ;
    m_near = 10.0;
    m_far = 30.0;
}

void MyGLItem::mousePressEvent(QMouseEvent *event)
{
    if(m_lastMouseEvent)
        delete m_lastMouseEvent;
    m_lastMouseEvent = new QMouseEvent(*event);
    m_lastMouseEvent->setAccepted(false);
}

void MyGLItem::paintUnderQmlScene()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawAxes();
    //m_cube->draw(renderer());
//    drawTriangles();
}

/**
 * @brief MyGLItem::paintOnTopOfQmlScene
 * Uncommend objects to be drawn
 */
void MyGLItem::paintOnTopOfQmlScene()
{
    //m_cube->draw(renderer());
    //drawAxes();
    //drawAxes();
    //drawTriangles();
    //m_sphere->draw(renderer());
    //m_frustum->draw(renderer());
    //m_mouseRay->draw(renderer());
    //drawF();
    //drawNormals();
    m_spaceship->draw(renderer());
}

void MyGLItem::setupGeometry()
{
    createCube(v_Zero, v_XYZ);
    createVisibleNormals();
    createTriangles();
    m_cube->makeSurface(NULL, NULL);
    //createAxes(6.0);
    m_geometryIsValid = true;
    m_spaceship->loadWavefrontFile(":/spaceship2",NULL,NULL);

    m_mainlopptimer->start();
}

void MyGLItem::createTriangles()
{
    //Now we create the geometry. Every corner needs a vertex, a normal, a color and a texture,
    //although normal and texture are not used for basic rendering.
    QVector3D v0 = QVector3D(0.0, 0.0, 0.0);
    QVector3D v1 = QVector3D(1.0, 0.0, 0.0);
    QVector3D v2 = QVector3D(0.0, 1.0, 0.0);
    QVector3D n0 = QVector3D(0.0, 0.0, 1.0); //dummy normal
    QVector3D t0 = QVector3D(0.0,0.0,0.0); //dummy texture

//    m_firstTriangleIndex = m_points.size(); //save start index
    m_firstTriangleIndex = m_indices.size(); //save start index
    //append the vertices for the triangle
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v0, n0, t0, GLColorRgba::clRed));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v1 * 0.3, n0, t0, GLColorRgba::clGreen));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 1.5, n0, t0, GLColorRgba::clBlue));

    m_indices.append(m_points.size());
    m_points.append(GLPoint(v1 * 0.3, n0, t0, GLColorRgba::clRed));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 1.5, n0, t0, GLColorRgba::clRed));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v1 * 0.3 + v2 * 1.5, n0, t0, GLColorRgba::clGreen));

    //rectangle top
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 1.2 + v1* 0.3, n0, t0, GLColorRgba::clRed));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 1.2 + v1* 0.9, n0, t0, GLColorRgba::clGreen));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 1.5 + v1* 0.9, n0, t0, GLColorRgba::clBlue));

    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 1.2 + v1* 0.3, n0, t0, GLColorRgba::clRed));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 1.5 + v1* 0.3, n0, t0, GLColorRgba::clBlue));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 1.5 + v1* 0.9, n0, t0, GLColorRgba::clBlue));

    //rectangle middle
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 0.6 + v1* 0.3, n0, t0, GLColorRgba::clRed));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 0.6 + v1* 0.6, n0, t0, GLColorRgba::clGreen));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 0.9 + v1* 0.6, n0, t0, GLColorRgba::clBlue));

    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 0.6 + v1* 0.3, n0, t0, GLColorRgba::clRed));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 0.9 + v1* 0.3, n0, t0, GLColorRgba::clBlue));
    m_indices.append(m_points.size());
    m_points.append(GLPoint(v2 * 0.9 + v1* 0.6, n0, t0, GLColorRgba::clBlue));
//    m_lastTriangleIndex = m_points.size() - 1; //save end index
    m_lastTriangleIndex = m_indices.size() - 1; //save end index
}

void MyGLItem::drawTriangles()
{
    renderer()->setLightingEnabled(m_lightingEnabled);
    renderer()->setColorArrayEnabled(m_colorArrayEnabled);
    renderer()->setTextureEnabled(false);
    //enable required arrays
    int stride = sizeof(GLPoint);
    renderer()->activateAttributeArray(GLESRenderer::VERTEX_LOCATION,
                                     m_points[0].vertexPointer(), stride);
    renderer()->activateAttributeArray(GLESRenderer::NORMAL_LOCATION,
                                        m_points[0].normalPointer(), stride);
    renderer()->activateAttributeArray(GLESRenderer::TEXCOORD_LOCATION,
                 m_points[0].texCoordPointer(), stride);
    renderer()->activateAttributeArray(GLESRenderer::COLOR_LOCATION,
                 m_points[0].colorPointer(), stride);

//    glDrawArrays(GL_TRIANGLES, m_firstTriangleIndex,
//                 m_lastTriangleIndex - m_firstTriangleIndex + 1);
    glDrawElements(GL_TRIANGLES, m_lastTriangleIndex - m_firstTriangleIndex + 1,
                   GL_UNSIGNED_SHORT, &m_indices.data()[m_firstTriangleIndex]);
    int error = glGetError();
    qDebug()<< "GL error: " << QString::number(error,16);
    renderer()->disableAttributeArrays();
}

void MyGLItem::drawCube()
{
    renderer()->setLightingEnabled(m_lightingEnabled);
    renderer()->setColorArrayEnabled(m_colorArrayEnabled);
    renderer()->setTextureEnabled(false);

    //enable required arrays
    int stride = sizeof(GLPoint);
    renderer()->activateAttributeArray(GLESRenderer::VERTEX_LOCATION,
                                     m_points[0].vertexPointer(), stride);
    renderer()->activateAttributeArray(GLESRenderer::NORMAL_LOCATION,
                                        m_points[0].normalPointer(), stride);
    renderer()->activateAttributeArray(GLESRenderer::TEXCOORD_LOCATION,
                 m_points[0].texCoordPointer(), stride);
    renderer()->activateAttributeArray(GLESRenderer::COLOR_LOCATION,
                 m_points[0].colorPointer(), stride);

    glDrawElements(GL_TRIANGLE_STRIP, m_lastCubeIndex - m_firstCubeIndex + 1,
                   GL_UNSIGNED_INT, &m_indices.data()[m_firstCubeIndex]);

    renderer()->disableAttributeArrays();
}


void MyGLItem::drawF()
{
    renderer()->pushMvMatrix();
    renderer()->scale(QVector3D(1.0, 5.0, 1.0));
    drawCube();
    drawNormals();
    renderer()->popMvMatrix();
    renderer()->pushMvMatrix();
    renderer()->translate(1.0,4.0,0.0);
    renderer()->scale(QVector3D(3.0, 1.0, 1.0));
    drawCube();
    drawNormals();
    renderer()->popMvMatrix();
    renderer()->pushMvMatrix();
    renderer()->translate(1.0,2.0,0.0);
    renderer()->scale(QVector3D(2.0, 1.0, 1.0));
    drawCube();
    drawNormals();
    renderer()->popMvMatrix();
}


void MyGLItem::timerTimeout()
{
    if(m_rotateX){
        m_guiThreadCameraMatrix.rotate(1.0, v_X);
        setRotationX(m_rotationX + 1.0);
    }
    if(m_rotateY){
        m_guiThreadCameraMatrix.rotate(1.0, v_Y);
        setRotationY(m_rotationY + 1.0);
    }
    if(m_rotateZ){
        m_guiThreadCameraMatrix.rotate(1.0, v_Z);
        setRotationZ(m_rotationZ + 1.0);
    }

    if(m_rotateX || m_rotateY || m_rotateZ){
        m_soundEngine->setEnabled(true);
        if(!m_soundEngine->isPlaying())
            m_soundEngine->playSound(":/sound/knock22050.wav");
    }
    else m_soundEngine->setEnabled(false);
    GLItem::timerTimeout();
}

void MyGLItem::mainloopTimeout()
{
    m_cube->move(QVector3D(0.01,0.0,0.0));
}

void MyGLItem::doSynchronizeThreads()
{
    m_cameraTransform = m_guiThreadCameraMatrix;

    if(m_zoomIn && m_eye.length() > m_near){
        m_eye *= 0.99;
        m_near *= 0.99;
        m_far *= 0.98;
    }

    if(m_zoomOut && m_eye.length() < m_far){
        m_eye /= 0.99;
        m_near /= 0.99;
        m_far /= 0.98;
    }
    if (m_zoomIn || m_zoomOut)
      qDebug() << "eye: " << m_eye << "  near: " << m_near << "  far: " << m_far;

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

