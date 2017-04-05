#ifndef GLFRUSTUM_H
#define GLFRUSTUM_H

#include "../glcore/glbody.h"
/**
 * @brief The GLFrustum class shows a wireframe set to the frustum settings when
 * draw() is called on a GLFrustum object with invalid surface. Use invalidateSurface() to readjust geometry.
 * Used for debugging scene settings.
 */
class GLFrustum : public GLBody
{
public:
    GLFrustum(const QString & name, const GLColorRgba & color = GLColorRgba::clBlue);
    /** Creates the lines forming the surface according to the settings in m_renderer.
      * Is called automatically by draw, if required.
      * MUST NOT be called without a working GL engine.
      *
      * @param pointContainer The container for the geometry data. If NULL, a new one is created.
      * @param indexContainer The container for the index data. If NULL, a new one is created.
      * Created containers will be deleted by destructor.
      */
    virtual void makeSurface(QVector<GLPoint> * pointContainer, QVector<GLuint> *indexContainer);

    /**
     * @brief invalidateSurface sets m_surfaceIsValid to false. This causes a call to makeSurface
     * when draw() is called.
     */
    void invalidateSurface(){m_surfaceIsValid = false;}

    /** Draws the surface and calls makeSurface if required.
      * Needs an active (made current) GL-Context.
      * Passes renderer to makeSurface by copying it to m_renderer.
      */
     virtual void draw(GLESRenderer * renderer);

 protected:
    GLESRenderer * m_renderer;
};

#endif // GLFRUSTUM_H
