#ifndef GLSKYSPHERERENDERER_H
#define GLSKYSPHERERENDERER_H

#include "../glcore/glesrenderer.h"


//### MÜSSEN EIN VSHADER UND FSHADER SCHREIBEN FÜR DIE SKYBOX EVTL

/**
 * @brief The SkySphereRenderer class
 * NOT IN USE!
 * For ,ore information see GLESRenderer
 *
 * Renderer for the SkySphere.
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class GLSkySphereRenderer : public GLESRenderer
{
public:
    GLSkySphereRenderer(QObject *parent,
                   const QString & vShaderFilename,
                   const QString & fShaderFilename );

    bool initialize();

    bool bind();

    void setPointLightEnabled(bool newVal);

    bool isPointLightEnabled() { return m_pointLightEnabled; }

    void setLightPosition(const QVector4D & newVal);

    const QVector4D lightPosition() { return m_lightPosition; }

    void setMvMatrix(const QMatrix4x4 newVal);

private:
    QVector4D m_lightPosition;

    bool m_pointLightEnabled;

    int m_location_uMvMatrix;
    int m_location_uPointLightEnabled;
    int m_location_uLightPos;
};

#endif // SkySphereRenderer_H
