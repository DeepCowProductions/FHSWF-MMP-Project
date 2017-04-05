#include "glcube.h"

GLCube::GLCube(const QString & name,const QVector3D& lbb, const QVector3D & rtf,
               const GLColorRgba & color, const QString textureFile)
    :GLBody(name, 1.0, color,textureFile)
{
   m_lbb = lbb;
   m_rtf = rtf;
   m_radius = (lbb - rtf).length() / 2.0;
}

void GLCube::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    m_drawingMode = GL_TRIANGLE_STRIP;
    m_firstPoint = m_points->size();
    m_firstIndex = m_indices->size();
    //corners
    QVector3D v0 = m_lbb;
    QVector3D vX = QVector3D(m_rtf.x(), m_lbb.y(), m_lbb.z());
    QVector3D vY = QVector3D(m_lbb.x(), m_rtf.y(), m_lbb.z());
    QVector3D vZ = QVector3D(m_lbb.x(), m_lbb.y(), m_rtf.z());
    QVector3D vXY = QVector3D(m_rtf.x(), m_rtf.y(), m_lbb.z());
    QVector3D vXZ = QVector3D(m_rtf.x(), m_lbb.y(), m_rtf.z());
    QVector3D vYZ = QVector3D(m_lbb.x(), m_rtf.y(), m_rtf.z());
    QVector3D vXYZ = m_rtf;

    //Left
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vY, -v_X, v_X, GLColorRgba::clMagenta));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(v0, -v_X, v_Zero, GLColorRgba::clMagenta));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vYZ, -v_X, v_XY, GLColorRgba::clMagenta));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vZ, -v_X, v_Y, GLColorRgba::clMagenta));
    m_indices->append(m_points->size()); //One degenerate triangle, we have to turn around the corner

    //Front
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vZ, v_Z, v_Zero, GLColorRgba::clRed));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXZ, v_Z, v_X, GLColorRgba::clRed));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vYZ, v_Z, v_Y, GLColorRgba::clRed));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXYZ, v_Z, v_XY, GLColorRgba::clRed));

    //Top
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXYZ, v_Y, v_XY, GLColorRgba::clYellow));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vYZ, v_Y, v_Y, GLColorRgba::clYellow));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXY, v_Y, v_X, GLColorRgba::clYellow));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vY, v_Y, v_Zero, GLColorRgba::clYellow));

    //Back
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vY, -v_Z, v_Y, GLColorRgba::clGreen));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXY, -v_Z, v_XY, GLColorRgba::clGreen));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(v0, -v_Z, v_Zero, GLColorRgba::clGreen));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vX, -v_Z, v_X, GLColorRgba::clGreen));

    //Bottom
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vX, -v_Y, v_Y, GLColorRgba::clBlue));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(v0, -v_Y, v_Zero, GLColorRgba::clBlue));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXZ, -v_Y, v_XY, GLColorRgba::clBlue));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vZ, -v_Y, v_X, GLColorRgba::clBlue));
    m_indices->append(m_points->size()); //One degenerate triangle, we have to turn around the corner

    //Right
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXZ, v_X, v_X, GLColorRgba::clCyan));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vX, v_X, v_Zero, GLColorRgba::clCyan));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXYZ, v_X, v_XY, GLColorRgba::clCyan));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXY, v_X, v_Y, GLColorRgba::clCyan));

    m_nextPoint = m_points->size();
    m_nextIndex = m_indices->size();
    findMinMaxCoordinates();
}
