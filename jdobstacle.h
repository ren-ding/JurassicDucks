/**
 *
 *  @file jdobstacle.h
 *
 *  @brief The head file of jdobstacle.cpp
 *
 *  @author Ren DING
 *  @date 29/08/12.
 *
 */

#ifndef __JDOBSTACLEH__
#define __JDOBSTACLEH__

#include "Vec3.h"
#include "glheaders.h"


class JDObstacle
{
protected:
    Vec3 position;          // obstacle's position
    GLUquadricObj* qobj;
    float radius;

public:
    JDObstacle(float x = 0, float y = 0,float z = 0);

    //get/set position
    void setPos(float x, float y,float z);
    Vec3 getPos() const;
    float getPosX() const;
    float getPosY() const;
    float getPosZ() const;

    //get radius
    float getRadius() const;

    //draw obstacle
    void drawJDObstacle();
};

#endif __JDOBSTACLEH__
