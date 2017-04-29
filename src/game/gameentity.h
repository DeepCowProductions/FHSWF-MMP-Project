#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "../glcore/glbody.h"
#include <QtMath>
#include "definesandconstants.h"



/**
 * @brief defines wich collision detection should be used by GameEntity's collision.
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
enum class CollisionType {AABB, SPHERE, AABB_SPHERE};

/**
 * @brief Struct to hold information about a single boundingBox.
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class  TAABB {
public:
    TAABB() {}
    TAABB(QVector3D max, QVector3D min) : max(max), min(min) {}

    QVector3D max;
    QVector3D min;
};

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
     * To be overwritten by subclass, this Base class function has nothing to check against except the playing field bounderies.
     * [...]
     * @param direction direction and distance to move the object along this vector
     * @return wether moving was succesfull
     */
    virtual bool tryMove(QVector3D direction);

    /**
     * @brief checkCollision for checking if collide with other
     * @param other with which want to check if colliding
     * @return if a collision was detected
     */
    virtual bool checkCollision(GameEntity * other);

    /**
     * @brief performCollDetection_AABBvsAABB
     * @param other GameEnitity, right hand side in regarts to funktion definition/delcaration.
     * @return true if colliding
     */
    virtual bool performCollDetection_AABBvsAABB(GameEntity * other);
    /**
     * @brief performCollDetection_SPHEREvsAABB
     * @param other GameEnitity, right hand side in regarts to funktion definition/delcaration.
     * @return true if colliding
     */
    virtual bool performCollDetection_SPHEREvsAABB(GameEntity * other);
    /**
     * @brief performCollDetection_AABBvsSPHERE
     * @param other GameEnitity, right hand side in regarts to funktion definition/delcaration.
     * @return true if colliding
     */
    virtual bool performCollDetection_AABBvsSPHERE(GameEntity * other);
    /**
     * @brief performCollDetection_SPHEREvsSPHERE
     * @param other GameEnitity, right hand side in regarts to funktion definition/delcaration.
     * @return true if colliding
     */
    virtual bool performCollDetection_SPHEREvsSPHERE(GameEntity * other);

    /**
     * @brief getCollisionType getter for the Collisiontype
     * @return the collisiontype
     */
    CollisionType getCollisionType() const;

    /**
     * @brief setCollisionType setter for the collisiontype
     * @param collisionType which want to set
     */
    void setCollisionType(const CollisionType &collisionType);

    /**
     * @brief transformation
     * @return the transformation matrix
     */
    QMatrix4x4 transformation() const;

    /**
     * @brief setTransformation set the transformation matrix
     * @param transformation the new transformation matrix
     */
    void setTransformation(const QMatrix4x4 &transformation);

    /**
     * @brief renderTransformation
     * @return the renderer transformation matrix
     */
    QMatrix4x4 renderTransformation() const;

    /**
     * @brief setRenderTransformation set the render transformation matrix
     * @param renderTransformation the new render transformation matrix
     */
    void setRenderTransformation(const QMatrix4x4 &renderTransformation);

    /**
    * @brief rotate the guiTransformation matrix
    * @param angle to rotate
    * @param axsis which want to rotate
    */
    void rotate(float angle, QVector3D axsis);

    /**
     * @brief translate the guiTransformation matrix
     * @param direction which want to translate
     */
    void translate (QVector3D direction);

    /**
     * @brief setRotationDirection which direction want to rotate
     * @param direction which want to rotate
     */
    void setRotationDirection (QVector3D direction);

    /**
     * @brief getVirtualCenter
     * @return the center of the entity
     */
    QVector3D getVirtualCenter() const;

    /**
     * @brief setVirtualCenter sets a new center of the entity
     * @param v new center
     */
    void setVirtualCenter(const QVector3D v);

    /**
     * @brief glModel returns the GLBody of the Entity
     * @return the GLBody
     */
    GLBody* glModel();

    //### operators
    virtual bool operator ==(GameEntity const& other);
    bool operator !=(GameEntity const& other);

    //### no setter on purpose!
    GameEngine *engine() const;

    /**
    * @brief getBoundingBox
    * @return the bounding box
    */
    TAABB *getBoundingBox() const;

    /**
     * @brief setBoundingBox sets a new bounding box
     * @param boundingBox which want to set
     */
    void setBoundingBox(TAABB *boundingBox);

private:
    //### for logic
    GameEngine * m_engine;

    //### the object
    GLBody * m_glModel;

    //### which collisiontype
    CollisionType m_collisionType;

    QMatrix4x4 m_guiTransformation; // owned by gui thread
    QMatrix4x4 m_renderTransformation; // owned by render thred to draw the element

    TAABB * m_boundingBox = nullptr;
};

#endif // GAMEENTITY_H
