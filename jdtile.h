/**
 *
 *  @file jdtile.h
 *
 *  @brief The head file of jdtile.cpp
 *
 *  @author Ren DING
 *  @date 07/10/12.
 *
 */

#ifndef __JDTILEH__
#define __JDTILEH__

#include "headers.h"
#include "Vec2.h"
#include "Vec3.h"
class JDMap;

class JDTile
{
protected:
    QVector<GLfloat> verts;
    QVector<GLfloat> rgba;
    QVector<GLfloat> tex;
    QVector<GLuint> idx;
public:
    JDTile();
    JDTile(JDMap jdmap,int i, int j, int w, int h, int whichPart);
    void render();
};

#endif // __JDTILEH__
