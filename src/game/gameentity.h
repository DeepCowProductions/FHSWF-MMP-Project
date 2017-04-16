#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "../glcore/glbody.h"
#include <QtMath>
#include "definesandconstants.h"


/*
 * defines which collision detection should be used by GameEntity's collision.
 */
//### forward decleration for class GameEngine to avoid circle inclusion.
class GameEngine;
/**
 * @brief The GameEntity class
 * Base class for storing Game Objects with a GLBody reference as VAO Object Model.
 *
 * Class holds a pointer reference to a GLBody Object wich is used for rendering,
 * as well as a specific transformation matrix wich gets applied to the model before rendering.
 * That way this class serves as an adapter for having multiple objects with the same vao model without duplicating it for every object.
 * A List of all objects should be kept somewhere.(in this project all objects are hold by an instance of @ref GameEngine)
 *
 * @attention make sure that the model passed in the constructor
 *  does not get deleted/moved before every instance of GameEntity holding that model is no longer in use,
 *  or alternatively update every instance of GameEntity (might not be thread save!).
 *
 * Should be subclassed for use with desired model and desired entity functions
 *  (such as animation, movement or similar things).
 *
 * Subclassing can also be used to make the entity hold and render more than one reference to an instance of GLBody.
 * The methods:
 * @code
 *  GameEntity::draw(GLESRenderer * renderer)
 *  GameEntity::syncForRendering()
 *  [...]
 * @endcode
 * should then be overwritten to process all new members (and call GameEntity::xyz() for their original functionalities).
 * See source code for details.
 *
 * Example usage:
 * @code
 * //### initialize OpenGl context
 * //### create vao model i.e. GLBody* myModel = new GLBody(...);
 *  GameEntity* ent = new GameEntity(myModel);
 * //### setup rendering for frame
 *  ent->snyForRendering();
 *  renderer->bind();     // renderer is type GLESRenderer
 *  ent->draw(renderer);
 *  renderer->release();
 * //### finish rendering for frame
 * @endcode
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class GameEntity
{
public:
    GameEntity(GameEngine * engine, GLBody * model);
    virtual ~GameEntity();

    virtual void draw(GLESRenderer * renderer);
    virtual void snycForRendering();

    /**
     * @brief tryMove calls GameEntity::translate after checking if movement is possible.
     * To be overwritten by subclass, this Base class function has nothing to check against.
     * [...]
     * @param direction direction and distance to move the object along this vector
     * @return wether moving was succesfull
     */
    virtual bool tryMove(QVector3D direction);
    virtual bool checkCollision(GameEntity * other);

    /**
     * @brief performCollDetection_AABBvsAABB
     * @param other GameEnitity, right hand side in regarts to funktion definition.
     * @return true if colliding
     */
    virtual bool performCollDetection_AABBvsAABB(GameEntity * other);
    virtual bool performCollDetection_SPHEREvsAABB(GameEntity * other);
    virtual bool performCollDetection_SPHEREvsSPHERE(GameEntity * other);

    CollisionType getCollisionType() const;
    void setCollisionType(const CollisionType &collisionType);

    QMatrix4x4 transformation() const;
    void setTransformation(const QMatrix4x4 &transformation);
    QMatrix4x4 renderTransformation() const;
    void setRenderTransformation(const QMatrix4x4 &renderTransformation);

    void rotate(float angle, QVector3D axsis);
    void translate (QVector3D direction);
    void setRotationDirection (QVector3D direction);
    QVector3D getVirtualCenter() const;
    void setVirtualCenter(const QVector3D v);

    GLBody* glModel();

    virtual bool operator ==(GameEntity const& other);
    bool operator !=(GameEntity const& other);

    //### no setter on purpose!
    GameEngine *engine() const;

    TAABB *getBoundingBox() const;
    void setBoundingBox(TAABB *boundingBox);

private:
    GameEngine * m_engine;
    GLBody * m_glModel;
    CollisionType m_collisionType;

    QMatrix4x4 m_guiTransformation; // owned by gui thread
    QMatrix4x4 m_renderTransformation; // owned by render thred to draw the element

    TAABB *m_boundingBox;
};

#endif // GAMEENTITY_H
