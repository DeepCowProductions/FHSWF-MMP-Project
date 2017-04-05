#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <QVector>
#include <QVector3D>
#include <QVector4D>
#include <fstream>
#include <sstream>
#include <GLES/gl.h>
#include <QDebug>

using namespace std;

/**
 * @brief The ObjLoader class was the first time we had to try load the wavefront file.
 *        But after a question, mister Roth has told that he had already implemented.
 *
 * @author Kuhmichel() and Grabelus(10044563)
 */
class ObjLoader
{
public:
    /**
     * @brief ObjLoader Constructor
     *
     * @param filename path of the wavefront file
     */
    ObjLoader(const char* filename);
    ~ObjLoader();

    /**
     * @brief load_obj here was try to load the wavefrontfile and parse it.
     */
    void load_obj();

    /**
     * @brief getVertices getter for the vertieces
     *
     * @return vertieces of the object
     */
    QVector<QVector3D> getVertices();

    /**
     * @brief getNormals getter for the normals
     *
     * @return normals of the object
     */
    QVector<QVector3D> getNormals();

    /**
     * @brief getElements getter for the order of points
     *
     * @return the order of points
     */
    QVector<GLuint> getElements();

private:
    const char* path;
    //### VARS OF THE WAVEFRONT FILE, WHERE ALL IS STORED
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<GLuint> elements;
};

#endif // OBJLOADER_H
