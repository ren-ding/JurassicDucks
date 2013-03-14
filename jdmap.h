/**
 *
 *  @file jdmap.h
 *
 *  @brief The head file of jdmap.cpp
 *
 *  @author Ren DING
 *  @date 06/10/12.
 *
 */

#ifndef __JDMAPH__
#define __JDMAPH__

#include "headers.h"
#include "Vec4.h"
#include "jdtile.h"
#include "jdtrees.h"

class JDMap
{
protected:
    QString dirName;
    //Conversion from pixel to X/Z, or gray level to Y
    float   scale;
    float   bounds[2];  //Real world width and height
    float   samples[2]; //Image width, height
    GLuint  texID;
    bool    shaded;

    QMap<QString, Vec4> TypeInfo;
    QVector<int> typeData;
    QVector<JDTile> jdtiles;
    JDTrees jdtrees;

public:
    JDMap(QString dirName);

    //convert utility
    int colorToType(int red);
    Vec4 typeColor(int t);

    //set/get functions
    QString getDirName() const;
    float getScale() const;
    float* getBounds();
    float* getSamples();
    void setShaded(bool isShaded);
    int getTypeColor(int index);

    //image texture handle functions
    void load(JDTrees jdtrees);
    void loadTypeData();
    void loadTextureMap();
    void createTiles();
    void loadTrees();
    void render();
};

#endif // __JDMAPH__
