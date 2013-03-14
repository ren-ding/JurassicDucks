/**
 *
 *  @file jdlight.cpp
 *
 *  @brief The class provide light parameters
 *
 *  @author Ren DING
 *  @date 30/08/12.
 *
 */

#include "jdlight.h"

JDLight::JDLight()
{
    this->ambient[0] = 0.0;
    this->ambient[1] = 0.0;
    this->ambient[2] = 0.0;
    this->ambient[3] = 1.0;

    this->diffuse[0] = 1.0;
    this->diffuse[1] = 1.0;
    this->diffuse[2] = 1.0;
    this->diffuse[3] = 1.0;

    this->specular[0] = 1.0;
    this->specular[1] = 1.0;
    this->specular[2] = 1.0;
    this->specular[3] = 1.0;

    this->position[0] = 0.0;
    this->position[1] = 1.0;
    this->position[2] = 1.0;
    this->position[3] = 0.0;

    this->lmodel_ambient[0] = 0.1;
    this->lmodel_ambient[1] = 0.1;
    this->lmodel_ambient[2] = 0.1;
    this->lmodel_ambient[3] = 1.0;


    this->noEmission[0] = 0.0;
    this->noEmission[1] = 0.0;
    this->noEmission[2] = 0.0;
    this->noEmission[3] = 1.0;
}

//
//turn on GL_LIGHT0
//
void JDLight::turnOn()
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
}
