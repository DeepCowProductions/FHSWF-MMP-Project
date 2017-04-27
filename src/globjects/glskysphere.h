#ifndef GLSKYSPHERE_H
#define GLSKYSPHERE_H

#include "../globjects/glsphere.h"

/**
 * @brief The GLSkySphere class
 *
 * The Class for the space suround the spaceship.
 *
 * @attention A Comment is with ### after // marked and written UPPERCASE.
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class GLSkySphere : public GLSphere {
public:
    GLSkySphere(const QString & name, float radius = 1.0, const GLColorRgba & color = GLColorRgba::clBlue,
                const QString textureFile = "",
                int stacks = 10, int slices = 18);

    void makeSurface(QVector<GLPoint> * pointContainer, QVector<GLuint> *indexContainer);
};

#endif // SkySphere_H
