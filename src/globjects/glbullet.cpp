#include "glbullet.h"


GLBullet::GLBullet(const QString & name, double length, double diameter, const GLColorRgba & color, const QString textureFile)
    :GLBody(name, 1.0, color,textureFile)
{
    m_length = length;
    m_diamenter = diameter;
}


void GLBullet::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    m_drawingMode = GL_TRIANGLE_STRIP;
//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    m_firstPoint = m_points->size();
    m_firstIndex = m_indices->size();

    //### helpers
    double l = m_length /2;
    int slices = 5;
    QMatrix4x4 m;
    QVector3D rf = QVector3D(0.0,l,m_diamenter);
    QVector3D rb = QVector3D(0.0,-l,m_diamenter);
    m.setToIdentity();

    //### verticies
    double s = 360 / slices;
    for (int i = 0; i < slices; i++){
        m.setToIdentity();
        m.rotate(s*i,v_Y);
        m_points->append(GLPoint(m*rf,m*v_Z,v_Zero,m_color));
        m_points->append(GLPoint(m*rb,m*v_Z,v_Zero,m_color));
    }
    int front = m_points->size();
    m_points->append(GLPoint(v_Y*l,v_Y,v_Zero,m_color));
    int back = m_points->size();
    m_points->append(GLPoint(-v_Y*l,v_Y,v_Zero,m_color));

    //### indicies
    /*
     *       *-------------*
     *      /|             |\
     *     / |             | \
     *    +  |             |  +
     *     \ |             | /
     *      \|             |/
     *       *-------------*
     */
    for (int i = 0; i < slices; i++){
        m.setToIdentity();
        m.rotate(s*i,v_Y);
        m_indices->append((front));
        m_indices->append((front));
        m_indices->append(( i*2     ));
        m_indices->append((((i*2) + 2))%(slices*2));
        m_indices->append((((i*2) + 1))%(slices*2));
        m_indices->append((((i*2) + 3))%(slices*2));
        m_indices->append((back));
        m_indices->append((back));
    }

    m_nextPoint = m_points->size();
    m_nextIndex = m_indices->size();
    findMinMaxCoordinates();
}


