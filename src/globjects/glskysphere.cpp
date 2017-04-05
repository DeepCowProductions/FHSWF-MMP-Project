#include "glskysphere.h"

GLSkySphere::GLSkySphere(const QString & name, float radius, const GLColorRgba & color,
                         const QString textureFile,
                         int stacks, int slices)
    :GLSphere(name,radius,color,textureFile,stacks,slices)
{
    m_stacks = stacks;
    m_slices = slices;
    m_drawingMode = GL_TRIANGLE_STRIP;
}

void GLSkySphere::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer)
{
    GLSphere::makeSurface(pointContainer, indexContainer);
}
