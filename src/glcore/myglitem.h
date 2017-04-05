#ifndef MYGLITEM_H
#define MYGLITEM_H

#include "glitem.h"
#include "../globjects/glcube.h"
#include "../globjects/glsphere.h"
#include "../globjects/glfrustum.h"
#include "../globjects/glmouseray.h"
#include "../globjects/glspaceship.h"
#include "../sound/soundengine.h"

class MyGLItem : public GLItem
{
    Q_OBJECT
    Q_PROPERTY(bool rotateX READ rotateX WRITE setRotateX NOTIFY rotateXChanged)
    Q_PROPERTY(bool rotateY READ rotateY WRITE setRotateY NOTIFY rotateYChanged)
    Q_PROPERTY(bool rotateZ READ rotateZ WRITE setRotateZ NOTIFY rotateZChanged)
    Q_PROPERTY(double rotationX READ rotationX WRITE setRotationX NOTIFY rotationXChanged)
    Q_PROPERTY(double rotationY READ rotationY WRITE setRotationY NOTIFY rotationYChanged)
    Q_PROPERTY(double rotationZ READ rotationZ WRITE setRotationZ NOTIFY rotationZChanged)
    Q_PROPERTY(bool zoomIn READ zoomIn WRITE setZoomIn NOTIFY zoomInChanged)
    Q_PROPERTY(bool zoomOut READ zoomOut WRITE setZoomOut NOTIFY zoomOutChanged)


public:
    MyGLItem(QQuickItem *parent = 0);
    ~MyGLItem();

    /**
     * @brief createCube Creates a cube from llb to rtf
     * @param lbb  left bottom back corner
     * @param rtf right top front corner
     */
    void createCube(const QVector3D& lbb, const QVector3D& rtf );
    void drawCube();

    /**
     * @brief MyGLItem::createVisibleNormals
     * Create a white line of length 1 for every normal vector
     */
    void createVisibleNormals();
    void drawNormals();


    bool rotateX() const
    {
        return m_rotateX;
    }

    bool rotateY() const
    {
        return m_rotateY;
    }

    bool rotateZ() const
    {
        return m_rotateZ;
    }

    double rotationX() const
    {
        return m_rotationX;
    }

    double rotationY() const
    {
        return m_rotationY;
    }

    double rotationZ() const
    {
        return m_rotationZ;
    }

    bool zoomIn() const
    {
        return m_zoomIn;
    }

    bool zoomOut() const
    {
        return m_zoomOut;
    }

public slots:
    /**
     * @brief resetView Reset all rotations
     */
    void resetView();

    void setRotateX(bool rotateX)
    {
        if (m_rotateX == rotateX)
            return;

        m_rotateX = rotateX;
        emit rotateXChanged(rotateX);
    }

    void setRotateY(bool rotateY)
    {
        if (m_rotateY == rotateY)
            return;

        m_rotateY = rotateY;
        emit rotateYChanged(rotateY);
    }

    void setRotateZ(bool rotateZ)
    {
        if (m_rotateZ == rotateZ)
            return;

        m_rotateZ = rotateZ;
        emit rotateZChanged(rotateZ);
    }

    void setRotationX(double rotationX)
    {
        if (m_rotationX == rotationX)
            return;

        m_rotationX = rotationX;
        emit rotationXChanged(rotationX);
    }

    void setRotationY(double rotationY)
    {
        if (m_rotationY == rotationY)
            return;

        m_rotationY = rotationY;
        emit rotationYChanged(rotationY);
    }

    void setRotationZ(double rotationZ)
    {
        if (m_rotationZ == rotationZ)
            return;

        m_rotationZ = rotationZ;
        emit rotationZChanged(rotationZ);
    }

    void setZoomIn(bool zoomIn)
    {
        if (m_zoomIn == zoomIn)
            return;

        m_zoomIn = zoomIn;
        emit zoomInChanged(zoomIn);
    }

    void setZoomOut(bool zoomOut)
    {
        if (m_zoomOut == zoomOut)
            return;

        m_zoomOut = zoomOut;
        emit zoomOutChanged(zoomOut);
    }


signals:
    void rotateXChanged(bool rotateX);

    void rotateYChanged(bool rotateY);

    void rotateZChanged(bool rotateZ);

    void rotationXChanged(double rotationX);

    void rotationYChanged(double rotationY);

    void rotationZChanged(double rotationZ);

    void zoomInChanged(bool zoomIn);

    void zoomOutChanged(bool zoomOut);

protected:
    /**
     * @brief mousePressEvent GUI thread mousePress handler
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);
    /**
     * @brief paintUnderQmlScene
     * Virtual function for painting under a QML scene. This function is called by paintBefore after
     * calling createGeometries and initializing and binding the renderer.
     * Overwrite in subclasses for painting geometries in m_points with the renderer.
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
    void setupGeometry();

    /**
     * @brief createTriangles Create a set of triangles forming the letter F.
     */
    void createTriangles();

    /**
     * @brief drawTriangles
     * Draws two triangles.
     */
    void drawTriangles();

    /**
     * @brief drawF draws an F
     */
    void drawF();

    /**
     * @brief timerTimeout update rotation angles.
     */
    virtual void timerTimeout();


    void mainloopTimeout();

    /**
     * @brief doSynchronizeThreads Copy data from GUI-thread to render-thread and vice versa.
     * setup m_cameraTransform
     */
    virtual void doSynchronizeThreads();


    int m_firstTriangleIndex;
    int m_lastTriangleIndex;

    int m_firstCubePoint;
    int m_lastCubePoint;
    int m_firstCubeIndex;
    int m_lastCubeIndex;
    int m_firstNormalPoint;
    int m_lastNormalPoint;


    //Rotation flags
    bool m_rotateX;
    bool m_rotateY;
    bool m_rotateZ;

    //rotation angles
    QMatrix4x4 m_guiThreadCameraMatrix;

    double m_rotationX;
    double m_rotationY;
    double m_rotationZ;

    //zoomFlags
    bool m_zoomIn;
    bool m_zoomOut;

    //initial and reset eye position
    QVector3D m_initialEyePos;

    //mouse event coordinates
    QMouseEvent * m_lastMouseEvent; //a copy of the last event, owned by GUI thread
    QPoint m_renderedMousePoint; // owned by render thread
    
    //Geometric objects
    GLCube * m_cube;
    GLSphere * m_sphere;
    GLFrustum * m_frustum;
    GLMouseRay * m_mouseRay;
    GLSpaceShip * m_spaceship;

    QTimer * m_mainlopptimer;
    //Sound
    SoundEngine * m_soundEngine;
};

#endif // MYGLITEM_H
