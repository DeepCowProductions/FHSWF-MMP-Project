#include "glfrustum.h"


GLFrustum::GLFrustum(const QString &name, const GLColorRgba &color)
    :GLBody(name, 1.0, color)
{
  setDrawingMode(GL_LINES);
}

void GLFrustum::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer)
{
    Q_UNUSED (pointContainer);
    Q_UNUSED (indexContainer);

   if(!m_renderer)
       return;
   //DO NOT call GLBody::makeSurface here, we need our own containers!
   if(m_firstPoint == m_nextPoint) //we have no points yet
   {
       m_points = new QVector<GLPoint>();
       m_indices = new QVector<GLuint>();
   }
   m_points->clear();
   m_indices->clear();
   m_firstPoint= m_points->size();
   m_firstIndex = m_indices->size();

   //now read the viewport
   GLint vp[4]; //order is: x,y w,h
   glGetIntegerv(GL_VIEWPORT, vp);
   QVector3D lbf, lbb, ltf, ltb, rtf, rtb, rbf, rbb; //lbf = left bottom front  rtb = right top back
   //now get the model space points for the corners one pixel inside the viewport
   m_renderer->calculateMousePoints(&lbf, &lbb, QPoint(vp[0] + 1,          vp[1] + 1));
   m_renderer->calculateMousePoints(&ltf, &ltb, QPoint(vp[0] + 1,          vp[1] - 1 + vp[3]));
   m_renderer->calculateMousePoints(&rtf, &rtb, QPoint(vp[0] - 1 + vp[2],  vp[1]  - 1 + vp[3]));
   m_renderer->calculateMousePoints(&rbf, &rbb, QPoint(vp[0]  - 1 + vp[2], vp[1] + 1));
   QVector3D normal = v_X;
   QVector3D texCoord = v_Zero;

   //define the line ends
   m_points->append(GLPoint(lbf, normal, texCoord, m_color)); //0
   m_points->append(GLPoint(lbb, normal, texCoord, m_color)); //1
   m_points->append(GLPoint(ltf, normal, texCoord, m_color)); //2
   m_points->append(GLPoint(ltb, normal, texCoord, m_color)); //3
   m_points->append(GLPoint(rtf, normal, texCoord, m_color)); //4
   m_points->append(GLPoint(rtb, normal, texCoord, m_color)); //5
   m_points->append(GLPoint(rbf, normal, texCoord, m_color)); //6
   m_points->append(GLPoint(rbb, normal, texCoord, m_color)); //7

   //set the indices front to back, bottom to top
   //left side, 4 lines
   m_indices->append(0);
   m_indices->append(1);
   m_indices->append(1);
   m_indices->append(3);
   m_indices->append(3);
   m_indices->append(2);
   m_indices->append(2);
   m_indices->append(0);

   //right side, 4 lines
   m_indices->append(6);
   m_indices->append(7);
   m_indices->append(7);
   m_indices->append(5);
   m_indices->append(5);
   m_indices->append(4);
   m_indices->append(4);
   m_indices->append(6);

   //front, 2 lines
   m_indices->append(0);
   m_indices->append(6);
   m_indices->append(2);
   m_indices->append(4);

   //back, 2 lines
   m_indices->append(1);
   m_indices->append(7);
   m_indices->append(3);
   m_indices->append(5);

   m_nextPoint = m_points->size();
   m_nextIndex = m_indices->size();
   findMinMaxCoordinates();
   m_surfaceIsValid = true;
}

void GLFrustum::draw(GLESRenderer *renderer)
{
    m_renderer = renderer; //set it for this drawing
    GLint oldLineWidth[4]; //just in case...
    glGetIntegerv(GL_LINE_WIDTH, oldLineWidth);
    glLineWidth(3);
    bool oldLighting = renderer->isLightingEnabled();
    renderer->setLightingEnabled(false);
    GLBody::draw(renderer);
    glLineWidth(oldLineWidth[0]);
    renderer->setLightingEnabled(oldLighting);
    m_renderer = NULL;
}
