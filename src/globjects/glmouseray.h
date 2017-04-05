#ifndef GLMOUSERAY_H
#define GLMOUSERAY_H

#include  "../glcore/glbody.h"

class GLMouseRay : public GLBody
{
public:
    GLMouseRay(const QString & name, float radius = 1.0, const GLColorRgba & color = GLColorRgba::clRed, const QString textureFile = "");
    virtual void setMousePosition(QPoint mousePosition);
    virtual void makeSurface(QVector<GLPoint> * pointContainer, QVector<GLuint> *indexContainer);
    virtual void draw(GLESRenderer * renderer);

protected:
    QPoint m_mousePosition;
    GLESRenderer * m_renderer;
};

#endif // GLMOUSERAY_H
