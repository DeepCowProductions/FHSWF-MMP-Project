#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include "glesrenderer.h"

/**
 * @brief The SkyBoxRenderer class
 *
 * #virtual intialize(), bind() and disableAttributeArrays() overwritten
 *
 */

class SkyBoxRenderer : public GLESRenderer
{
public:
    explicit SkyBoxRenderer(QObject *parent,
                   const QString & vShaderFilename,
                   const QString & fShaderFilename );

    /**
      * Compile shaders, get attribute and uniform locations of shaders.
      * This function needs an active OpenGL context.
      * Returns false, if initialization failed.
      */
    virtual bool initialize();

    /**
      * Bind program and transfer attribute and uniform data to the shaders.
      * Calls initialize, if not alraedy initialized.
      * Returns false, if binding failed.
      */
    virtual bool bind();
protected:

    //### extra uniforms
    int m_location_uSkyBoxDummy;
    int m_location_uMvMatrix;

    //### shader varibles
    float m_uSkyBoxDummy;
//    QMatrix4x4 m_uMvMatrix; // already present as m_MvMatrix in base class

};

#endif // SKYBOXRENDERER_H
