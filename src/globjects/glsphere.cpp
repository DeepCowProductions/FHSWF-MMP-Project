#include "glsphere.h"

GLSphere::GLSphere(const QString &name, float radius, const GLColorRgba &color,
                   const QString textureFile, int stacks, int slices)
 :GLBody(name, radius,color, textureFile )
{
  m_stacks = stacks;
  m_slices = slices;
  m_drawingMode = GL_TRIANGLE_STRIP;
}

void GLSphere::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    m_firstPoint = m_points->size();
    m_firstIndex = m_indices->size();

    QVector3D vertex;
    QVector3D normal;
    GLColorRgba color = m_color;
    QVector3D texCoord;
    QMatrix4x4 stackRotor;
    QMatrix4x4 sliceRotor;
    for(int slice = 0; slice <= m_slices; slice++)
    {
        double longitude = 360.0 / m_slices * slice;
        if(slice == m_slices)
            longitude = 0.0;
        sliceRotor.setToIdentity();
        sliceRotor.rotate(longitude, v_Z);
        for(int stack = -m_stacks /2; stack <= m_stacks /2; stack ++)
        {
           vertex = v_X;
           stackRotor.setToIdentity();
           double latitude = 180.0 / m_stacks * stack;
           stackRotor.rotate(latitude, -v_Y);
           vertex = sliceRotor * stackRotor * vertex;
           normal = vertex;
           vertex = vertex * m_radius;
           //texture coordinates for "Plate Carée" projection of texture image
           texCoord = QVector3D( (double)slice / (double)m_slices,
                                0.5 + (double)stack / (double)m_stacks,
                                0.0);
           m_points->append(GLPoint(vertex, normal, texCoord, color));
        }
    }

    QVector3D southPole = -v_Z * m_radius;
    normal = -v_Z;
    m_points->append(GLPoint(southPole, normal, texCoord));

    QVector3D northPole = -southPole;
    normal = -normal;
    m_points->append(GLPoint(northPole, normal, texCoord));

    // create indices

    for(int slice = 0; slice < m_slices; slice +=2)
    {
        for(int stack = 0; stack <= m_stacks; stack ++){
            m_indices->append(stack + slice * (m_stacks +1));
            m_indices->append(stack + slice * (m_stacks +1) + m_stacks +1);
        }

        for(int stack = m_stacks; stack >= 0; stack --)
        {
            m_indices->append(stack + (slice + 2) * (m_stacks +1));
            m_indices->append(stack +(slice + 2) * (m_stacks +1) - m_stacks - 1);
        }

    }

    m_nextPoint = m_points->size();
    m_nextIndex = m_indices->size();
    findMinMaxCoordinates();
}
