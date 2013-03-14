/**
 *
 *  @file jdterrain.h
 *
 *  @brief The head file of jdterrain.cpp
 *
 *  @author Ren DING
 *  @date 08/08/12.
 *
 */

#ifndef __JDTERRAINH__
#define __JDTERRAINH__

#include "glheaders.h"
#include "jdtile.h"

class JDTerrain
{
protected:
    GLfloat terrainWidth, terrainThick, terrainHeight;
    GLuint texID;
    QVector<JDTile> jdtiles;
public:
    JDTerrain(GLfloat terrainWidth, GLfloat terrainThick, GLfloat terrainHeight);
    virtual ~JDTerrain();

    void loadTextureMap();
    void createTiles();
    void drawTerrain();
};

#endif // __JDTERRAINH__
