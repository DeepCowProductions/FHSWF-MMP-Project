#ifndef GLSPACESHIP_H
#define GLSPACESHIP_H

#include  "../glcore/glbody.h"
#include "../glcore/objloader.h"

/**
 * @brief The GLSpaceShip class is the Spaceship of the player for the Space Invaders.
 *
 * @attention A Comment is with ### after // marked and written UPPERCASE.
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class GLSpaceShip : public GLBody
{
public:
    /**
     * @brief GLSpaceShip Constructor of the Spaceship
     */
    GLSpaceShip();
    GLSpaceShip(const QString &name, float radius = 1.0, const GLColorRgba &color = GLColorRgba::clGray, const QString textureFile = "");

    void makeSurface(QVector<GLPoint> *pointContainer, QVector<GLuint> *indexContainer);
    void makeSurface();

    /**
     * @brief loadWavefrontFile here we load the wavefront file of the spaceship(player)
     *
     * @param fileName path of wavefront file
     * @param pointContainer for vertieces
     * @param indexContainer for indices
     * @return
     */
    bool loadWavefrontFile(const QString &fileName, QVector<GLPoint> *pointContainer, QVector<GLuint> * indexContainer);

private:
    //### NOT IN USE
    QVector<QVector3D> spaceship_vertices;
    QVector<QVector3D> spaceship_normals;
    QVector<GLuint> spaceship_elements;
    ObjLoader *spaceshipLoader;
};

#endif // GLSPACESHIP_H
