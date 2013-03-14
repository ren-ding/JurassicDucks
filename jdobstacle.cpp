/**
 *
 *  @file jdobstacle.cpp
 *
 *  @brief The class specify obstacle model
 *
 *  @author Ren DING
 *  @date 25/08/12.
 *
 */

#include "jdobstacle.h"
#include "jdUtility.h"

JDObstacle::JDObstacle(float x, float y, float z)
{
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->radius = 5.0;
}

void JDObstacle::setPos(float x, float y, float z) {
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
}

Vec3 JDObstacle::getPos() const
{
    return this->position;
}

float JDObstacle::getPosX() const{
    return this->position[0];
}

float JDObstacle::getPosY() const{
    return this->position[1];
}

float JDObstacle::getPosZ() const{
    return this->position[2];
}

//get radius
float JDObstacle::getRadius() const
{
    return this->radius;
}

void JDObstacle::drawJDObstacle() {
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glColor3fv(jdUtility::COLOR_RED);
        this->qobj = gluNewQuadric();
        gluQuadricDrawStyle(this->qobj, GLU_FILL);
        gluSphere(	this->qobj,
                    this->radius,   // radius
                    20,             // slices
                    20);
    glPopMatrix();
}
