/**
 *
 *  @file jdtree.h
 *
 *  @brief The head file of jdtree.cpp
 *
 *  @author Ren DING
 *  @date 09/10/12.
 *
 */

#ifndef __JDTREEH__
#define __JDTREEH__

#include "Vec2.h"
#include "Vec3.h"
#include "headers.h"

class JDTree
{
protected:
    Vec3 pos;
    int tag;
    Vec2 scale;     //horizontal and vertical scale
    float radius;

public:
    JDTree();
    JDTree(float x,float y,float z,int tag,float hScale,float vScale);

    //set/get functions
    int getTag() const;
    Vec3 getPos() const;
    float getPosX() const;
    float getPosY() const;
    float getPosZ() const;

    float getHScale() const;
    float getVScale() const;

    float getRadius() const;
    //to string
    QString toString();
};

#endif // __JDTREEH__
