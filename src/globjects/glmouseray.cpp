#include "glmouseray.h"

#include "../glcore/glcolorrgba.h"

GLMouseRay::GLMouseRay(const QString &name, float radius, const GLColorRgba &color, const QString textureFile)
    :GLBody(name, radius, color, textureFile)
{
  m_renderer = NULL;
}

void GLMouseRay::setMousePosition(QPoint mousePosition)
{
    m_mousePosition = mousePosition;
    m_surfaceIsValid = false;
}

void GLMouseRay::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer)
{
   if(!m_renderer)
       return;
   if(pointContainer == NULL)
   {
       m_points = new QVector<GLPoint>();
       m_ownPointsContainer = true;
   }
   else m_points->clear();
   if(indexContainer == NULL)
   {
       m_indices = new QVector<GLuint>();
       m_ownIndexContainer = true;
   }
   else m_indices->clear();

   QVector3D nearPoint, farPoint;

   m_renderer->calculateMousePoints(&nearPoint, &farPoint, m_mousePosition);

   QVector3D normal = v_X;
   QVector3D texCoord = v_Zero;
   m_firstPoint = m_points->size();
   m_firstIndex = m_indices->size();
   m_points->append(GLPoint(nearPoint, normal,texCoord, m_color));
   m_points->append(GLPoint(farPoint, normal,texCoord, m_color));
   m_nextPoint = m_points->size();
   m_nextIndex = m_indices->size();

   m_surfaceIsValid = true;
}

void GLMouseRay::draw(GLESRenderer *renderer)
{
    m_renderer = renderer;
    GLint oldPointSize = renderer->pointSize();
    renderer->setPointSize(4);
    bool oldLightingEnabled = renderer->isLightingEnabled();

    renderer->setLightingEnabled(false);
    setDrawingMode(GL_LINES);
    GLBody::draw(renderer);
    setDrawingMode(GL_POINTS);
    GLBody::draw(renderer);

    renderer->setLightingEnabled(oldLightingEnabled);
    renderer->setPointSize(oldPointSize);
    m_renderer = NULL;
}
