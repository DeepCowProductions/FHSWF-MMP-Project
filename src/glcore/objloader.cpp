#include "objloader.h"
#include "iostream"

ObjLoader::ObjLoader(const char* filename)
{
    this->path = filename;

}

void ObjLoader::load_obj()
{
    ifstream in(path, ios::in);
    if (!in)
    {
        qDebug() << "Cannot open " << path << endl; exit(1);
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            QVector3D v;
            float x, y, z;
            s >> x; s >> y; s >> z;
            v.setX(x);
            v.setY(y);
            v.setZ(z);
            vertices.push_back(v);
            //qDebug() << x << " " << y << " " << z;
        }
        else if (line.substr(0,2) == "f ")
        {
            GLuint a,b,c;
            string line2 = line.substr(2);
                size_t pos = line2.find_first_of("//");
                istringstream s(line2.substr(0,pos));
                s >> a;
                line2.erase(0,pos+2);
                size_t pos2 = line2.find(" ");
                size_t posSlash = line2.find("//");
                istringstream s1(line2.substr(pos2,posSlash));
                s1 >> b;
                line2.erase(0,posSlash+2);
                size_t pos3 = line2.find(" ");
                posSlash = line2.find(("//"));
                istringstream s2(line2.substr(pos3,posSlash));
                s2 >> c;
                elements.push_back(a); elements.push_back(b); elements.push_back(c);
                //qDebug() << a << " " << b << " " << c;
        }
        else if (line[0] == '#')
        {
            /* ignoring this line */
        }
        else
        {
            /* ignoring this line */
        }
    }

    normals.resize(vertices.size());
    for (int i = 0; i < elements.size(); i+=3)
    {
        GLushort ia = elements[i];
        GLushort ib = elements[i+1];
        GLushort ic = elements[i+2];

        QVector3D normal = QVector3D::crossProduct(
                    QVector3D(vertices[ib]) - QVector3D(vertices[ia]),
                    QVector3D(vertices[ic]) - QVector3D(vertices[ia]));
        normal.normalize();
        normals[ia] = normals[ib] = normals[ic] = normal;
    }
}

QVector<QVector3D> ObjLoader::getVertices()
{
    return vertices;
}

QVector<QVector3D> ObjLoader::getNormals()
{
    return normals;
}

QVector<GLuint> ObjLoader::getElements()
{
    return elements;
}
