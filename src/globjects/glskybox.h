#ifndef GLSKYBOX_H
#define GLSKYBOX_H

#include "../glcore/glbody.h"

class GLSkyBox : public GLBody
{
public:
    GLSkyBox(const QString & name,const double radius,
            const GLColorRgba & color = GLColorRgba::clBlue);
    // GLBody interface
public:
    virtual void makeSurface(QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer);
    virtual void draw(GLESRenderer *renderer);

private:

    QVector3D m_lbb;
    QVector3D m_rtf;
};

#endif // GLSKYBOX_H
