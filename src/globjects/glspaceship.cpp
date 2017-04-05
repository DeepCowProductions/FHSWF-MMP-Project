#include "glspaceship.h"

GLSpaceShip::GLSpaceShip(const QString &name, float radius, const GLColorRgba &color, const QString textureFile)
    :GLBody(QString("3D Spaceship"),radius,color,textureFile)
{
    (void)name;
    // war ein Versuch bis mir Herr Roth den Hinweis auf GLBody::loadWavefrontFile
    /*spaceshipLoader = new ObjLoader("/home/student/Desktop/MMP/models/spaceship/spaceship.obj");
    spaceshipLoader->load_obj();
    spaceship_vertices = spaceshipLoader->getVertices();
    spaceship_normals = spaceshipLoader->getNormals();
    spaceship_elements = spaceshipLoader->getElements();*/

    //qDebug() << spaceship_vertices.size();
}

void GLSpaceShip::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer) {
    GLBody::makeSurface(pointContainer,indexContainer);
    GLBody::setDrawingMode(GL_TRIANGLES);
    m_firstIndex = m_indices->size(); //save start index
    m_firstPoint = m_points->size(); // save the start point

    for(int i = 0; i < spaceship_vertices.size(); i++) {
        //m_indices->append(spaceship_elements.at(i));
        m_indices->append(m_points->size());
        //qDebug() << spaceship_vertices.at(i);
        //qDebug() << spaceship_elements.at(i);
        m_points->append(GLPoint(spaceship_vertices.at(i),spaceship_normals.at(i),QVector3D(0.0,0.0,0.0),GLColorRgba::clGray));
    }
    m_nextIndex = m_indices->size(); //save end index
    m_nextPoint = m_points->size(); //save end point
}

void GLSpaceShip::makeSurface()
{
    makeSurface(m_points,m_indices);
}

bool GLSpaceShip::loadWavefrontFile(const QString &fileName, QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer)
{
    return GLBody::loadWavefrontFile(fileName,pointContainer,indexContainer);
}
