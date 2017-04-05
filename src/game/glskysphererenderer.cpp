#include "glskysphererenderer.h"

/**
 * @brief GLSkySphereRenderer::GLSkySphereRenderer
 *        This Class is not in Use!!!
 *
 * @param parent
 * @param vShaderFilename
 * @param fShaderFilename
 */
GLSkySphereRenderer::GLSkySphereRenderer(QObject *parent,
                               const QString & vShaderFilename,
                               const QString & fShaderFilename )
    :GLESRenderer(parent, vShaderFilename, fShaderFilename)
{
    this->m_fShaderFileName = fShaderFilename;
    this->m_vShaderFileName = vShaderFilename;

    m_pointLightEnabled = false;
    m_lightPosition = QVector4D(0.0, 0.0, 0.0, 0.0);

    m_location_uLightPos = -1;
    m_location_uPointLightEnabled = -1;
    m_location_uMvMatrix = -1;
}

bool GLSkySphereRenderer::initialize()
{
    m_location_uLightingEnabled = m_renderProgram->uniformLocation("u_PointLightEnabled");
    m_location_uMvMatrix = m_renderProgram->uniformLocation("u_MvMatrix");
    m_location_uLightPos = m_renderProgram->uniformLocation("u_LightPos");
    return GLESRenderer::initialize();
}

bool GLSkySphereRenderer::bind()
{
    if(m_location_uLightPos != -1)
        m_renderProgram->setUniformValue(m_location_uLightPos,m_lightPosition);
    if(m_location_uMvMatrix != -1)
        m_renderProgram->setUniformValue(m_location_uMvMatrix,m_mvMatrix);
    if(m_location_uPointLightEnabled != -1)
        m_renderProgram->setUniformValue(m_location_uPointLightEnabled,m_pointLightEnabled);
    return GLESRenderer::bind();
}

void GLSkySphereRenderer::setPointLightEnabled(bool newVal)
{
    m_pointLightEnabled = newVal;
    if(m_bound && (m_location_uPointLightEnabled != -1))
        m_renderProgram->setUniformValue(m_location_uPointLightEnabled, m_pointLightEnabled);
}

void GLSkySphereRenderer::setLightPosition(const QVector4D &newVal)
{
    m_lightPosition = newVal;
#ifdef DEBUG_GLESRENDERER
    ShaderDebugger::debugVector3D(m_lightDirection, "GLESRenderer uses lightDirection in object space:");
#endif
    QMatrix4x4 nMatrix = QMatrix4x4(m_normalMatrix);
    m_lightDirection = (nMatrix * m_lightDirection).normalized();//transform to eye space
    m_halfPlaneVector = (m_lightDirection + QVector3D(0.0,0.0,1.0)).normalized();//eye direction is 0,0,1 in eye space
#ifdef DEBUG_GLESRENDERER
    ShaderDebugger::debugVector3D(m_lightDirection, "GLESRenderer uses lightDirection in eye space:");
    ShaderDebugger::debugVector3D(m_lightDirection, "GLESRenderer uses halfplane vector in eye space:");
#endif
    if(m_bound && (m_location_uLightPos != -1))
      m_renderProgram->setUniformValue(m_location_uLightPos, m_lightPosition);
    if(m_bound && m_location_uHalfPlaneVector != -1)
        m_renderProgram->setUniformValue(m_location_uHalfPlaneVector, m_halfPlaneVector);
}

void GLSkySphereRenderer::setMvMatrix(const QMatrix4x4 newVal)
{
    if(m_bound && (m_location_uMvMatrix != -1))
        m_renderProgram->setUniformValue(m_location_uMvMatrix,m_mvMatrix);
    GLESRenderer::setMvMatrix(newVal);
}
