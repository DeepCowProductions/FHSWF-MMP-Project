#ifndef GLBULLET_H
#define GLBULLET_H

#include "../glcore/glbody.h"
#include "../game/definesandconstants.h"

class GLBullet : public GLBody
{
public:
    GLBullet(const QString & name, double length, double diameter,
             const GLColorRgba & color = GLColorRgba::clBlue, const QString textureFile = "");
    /**
    * To be overwritten by subclasses. GLESBody::createSurface should be called at the beginning
    * of overriding functions. It will create the pointContainer, if none is supplied
    * Is called automatically by draw, if required.
    * MUST NOT be called without a working GL engine.
    *
    * @param pointContainer The container for the geometry data. If NULL, a new one is created.
    * @param indexContainer The container for the index data. If NULL, a new one is created.
    * Created containers will be deleted by destructor.
    */
    virtual void makeSurface(QVector<GLPoint> * pointContainer, QVector<GLuint> *indexContainer);

    double length() const;
    double diamenter() const;

private:
    double m_length;
    double m_diamenter;

};

#endif // GLBULLET_H
