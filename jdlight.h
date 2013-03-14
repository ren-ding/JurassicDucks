/**
 *
 *  @file jdlight.h
 *
 *  @brief The head file of jdlight.cpp
 *
 *  @author Ren DING
 *  @date 30/08/12.
 *
 */

#ifndef __JDLIGHTH__
#define __JDLIGHTH__

#include "glheaders.h"

class JDLight
{
protected:
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat position[4];
    GLfloat lmodel_ambient[4];

    GLfloat noEmission[4];


public:
    JDLight();
    //turn on GL_LIGHT0
    void turnOn();
};

#endif // __JDLIGHTH__
