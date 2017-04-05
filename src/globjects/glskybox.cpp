#include "glskybox.h"


GLSkyBox::GLSkyBox(const QString & name,const double radius,
               const GLColorRgba & color)
    :GLBody(name, 1.0, color,"")
{
    double t = sqrt(3)*radius;
    m_lbb = QVector3D(t,t,t);
    m_rtf = -m_lbb;
    m_radius = radius;
}


void GLSkyBox::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    m_drawingMode = GL_TRIANGLE_STRIP;
//    glPolygonMode(GL_BACK,GL_LINE);
    m_firstPoint = m_points->size();
    m_firstIndex = m_indices->size();
    //corners
    QVector3D v0 = m_lbb;
    QVector3D vX = QVector3D(m_rtf.x(), m_lbb.y(), m_lbb.z());
    QVector3D vY = QVector3D(m_lbb.x(), m_rtf.y(), m_lbb.z());
    QVector3D vZ = QVector3D(m_lbb.x(), m_lbb.y(), m_rtf.z());
    QVector3D vXY = QVector3D(m_rtf.x(), m_rtf.y(), m_lbb.z());
    QVector3D vXZ = QVector3D(m_rtf.x(), m_lbb.y(), m_rtf.z());
    QVector3D vYZ = QVector3D(m_lbb.x(), m_rtf.y(), m_rtf.z());
    QVector3D vXYZ = m_rtf;

    //Left
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vY, -v_X, v_X, GLColorRgba::clMagenta));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(v0, -v_X, v_Zero, GLColorRgba::clMagenta));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vYZ, -v_X, v_XY, GLColorRgba::clMagenta));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vZ, -v_X, v_Y, GLColorRgba::clMagenta));
    m_indices->append(m_points->size()); //One degenerate triangle, we have to turn around the corner

    //Front
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vZ, v_Z, v_Zero, GLColorRgba::clRed));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXZ, v_Z, v_X, GLColorRgba::clRed));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vYZ, v_Z, v_Y, GLColorRgba::clRed));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXYZ, v_Z, v_XY, GLColorRgba::clRed));

    //Top
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXYZ, v_Y, v_XY, GLColorRgba::clYellow));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vYZ, v_Y, v_Y, GLColorRgba::clYellow));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXY, v_Y, v_X, GLColorRgba::clYellow));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vY, v_Y, v_Zero, GLColorRgba::clYellow));

    //Back
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vY, -v_Z, v_Y, GLColorRgba::clGreen));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXY, -v_Z, v_XY, GLColorRgba::clGreen));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(v0, -v_Z, v_Zero, GLColorRgba::clGreen));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vX, -v_Z, v_X, GLColorRgba::clGreen));

    //Bottom
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vX, -v_Y, v_Y, GLColorRgba::clBlue));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(v0, -v_Y, v_Zero, GLColorRgba::clBlue));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXZ, -v_Y, v_XY, GLColorRgba::clBlue));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vZ, -v_Y, v_X, GLColorRgba::clBlue));
    m_indices->append(m_points->size()); //One degenerate triangle, we have to turn around the corner

    //Right
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXZ, v_X, v_X, GLColorRgba::clCyan));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vX, v_X, v_Zero, GLColorRgba::clCyan));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXYZ, v_X, v_XY, GLColorRgba::clCyan));
    m_indices->append(m_points->size());
    m_points->append(GLPoint(vXY, v_X, v_Y, GLColorRgba::clCyan));

    m_nextPoint = m_points->size();
    m_nextIndex = m_indices->size();
    findMinMaxCoordinates();
}


/**
* @brief GLSkyBox::draw
*  -> slightly changed to draw a perspectiveless skybox
* @param renderer
*/
void GLSkyBox::draw(GLESRenderer *renderer)
{
    if(!m_surfaceIsValid)
        makeSurface(NULL, NULL);
    if(!m_points || m_points->size() == 0) //check for existing points
    {
        qDebug()<< m_name + " GLBody::draw  ERROR: No points!";
        return;
    }
    int stride = sizeof(GLPoint);
    bool textureEnabled = renderer->isTextureEnabled();
    bool lightingEnabled = renderer->isLightingEnabled();
    bool colorArrayEnabled = renderer->isColorArrayEnabled();

    //set colors
    renderer->setAmbientAndDiffuseColor(m_color);

    //enable required arrays
    renderer->activateAttributeArray(GLESRenderer::VERTEX_LOCATION,
                                     m_points->data()[0].vertexPointer(), stride);
    if (renderer->isLightingEnabled())
        renderer->activateAttributeArray(GLESRenderer::NORMAL_LOCATION,
                                         m_points->data()[0].normalPointer(), stride);
    if(m_textureIds.size() > 0){
        QOpenGLFunctions glFuncs(QOpenGLContext::currentContext());
        glFuncs.glActiveTexture(GL_TEXTURE0); //use texture unit 0
        glBindTexture(GL_TEXTURE_2D, m_textureIds[m_activeTextureIndex]);
        renderer->setTextureEnabled(true);
    }
    else renderer->setTextureEnabled(false);
    renderer->activateAttributeArray(GLESRenderer::TEXCOORD_LOCATION,
                                     m_points->data()[0].texCoordPointer(), stride);
    renderer->activateAttributeArray(GLESRenderer::COLOR_LOCATION,
                                     m_points->data()[0].colorPointer(), stride);

    //   for(int i = 0; i < indices.count(); i++)
    //    points[indices[i]].debugOutput("Point" +QString::number(i) + ":" + QString::number(indices[i]) + " ");

    calculateDrawMatrix();
    renderer->pushMvMatrix();
    renderer->addTransformation(m_drawMatrix);

    if(m_firstIndex >= 0 && m_nextIndex > 0)
        glDrawElements(m_drawingMode, m_nextIndex -m_firstIndex,
                       GL_UNSIGNED_INT, &m_indices->data()[m_firstIndex]);
    else
        glDrawArrays(m_drawingMode, m_firstPoint, m_nextPoint - m_firstPoint);

    if(lightingEnabled)
        renderer->setLightingEnabled(false);
    if(!colorArrayEnabled)
        renderer->setColorArrayEnabled(true);
    renderer->setTextureEnabled(false);
    if(m_showNormals)
        glDrawElements(GL_LINES, m_nextNormalIndex -m_firstNormalIndex,
                       GL_UNSIGNED_INT, &m_indices->data()[m_firstNormalIndex]);
    if(m_showFrame)
    {
        //draw the frame
        GLfloat lineWidth[4]; //4 floats, just for safety
        glGetFloatv(GL_LINE_WIDTH, lineWidth);
        glLineWidth(3.0);
        glDrawElements(GL_LINES, m_nextFrameIndex -m_firstFrameIndex,
                       GL_UNSIGNED_INT, &m_indices->data()[m_firstFrameIndex]);
        //Draw the hit line
        if(m_firstHitPoint != 0)
        {
            glLineWidth(5.0);
            glDrawArrays(GL_LINES, m_firstHitPoint, m_nextHitPoint - m_firstHitPoint);
        }
        glLineWidth(lineWidth[0]);
    }

    if(isSelected())
    {
        GLColorRgba pointColor(m_color.inverted());
        renderer->setAmbientAndDiffuseColor(pointColor);
#ifdef GLES
        glDrawArrays(GL_POINTS, m_firstPoint, m_nextPoint - m_firstPoint);
#else
        int oldPointSize = renderer->pointSize();
        renderer->setPointSize(5);
        glDrawArrays(GL_POINTS, m_firstPoint, m_nextPoint - m_firstPoint);
        renderer->setPointSize(oldPointSize);
#endif
    }

    //cleanup
    renderer->setLightingEnabled(lightingEnabled);
    renderer->setColorArrayEnabled(colorArrayEnabled);
    renderer->setTextureEnabled(textureEnabled);
    renderer->disableAttributeArrays();
    renderer->popMvMatrix();
}
