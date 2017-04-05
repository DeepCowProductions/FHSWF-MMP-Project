#include "skyboxrenderer.h"

SkyBoxRenderer::SkyBoxRenderer(QObject *parent,
                               const QString & vShaderFilename,
                               const QString & fShaderFilename )
    :GLESRenderer(parent,vShaderFilename,fShaderFilename)
{

    //### init for extra uniforms
    m_location_uSkyBoxDummy = -1;
    m_location_uMvMatrix = -1;


}

bool SkyBoxRenderer::initialize()
{
    GLESRenderer::initialize();

    m_location_uSkyBoxDummy = m_renderProgram->uniformLocation("u_PointSize");
    m_location_uMvMatrix = m_renderProgram->uniformLocation("u_MvMatrix");

//    return m_bound;
    return true;
}

bool SkyBoxRenderer::bind()
{
    GLESRenderer::bind();

    if(m_location_uSkyBoxDummy != -1)
        m_renderProgram->setUniformValue(m_location_uSkyBoxDummy, m_uSkyBoxDummy);
    if(m_location_uMvMatrix != -1)
        m_renderProgram->setUniformValue(m_location_uMvMatrix, m_mvMatrix);
//    return m_initialized;
    return true;
}
