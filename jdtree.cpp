/**
 *
 *  @file jdtree.cpp
 *
 *  @brief Geometry for tree. Just a pair of quads at 90 degree angles, so
 *  looks roughly the same from all directions. Texture map must have
 *  transparent background to give irregular shape
 *
 *  @author Ren DING
 *  @date 09/10/12.
 *
 */

#include "jdtree.h"
#include "headers.h"

JDTree::JDTree()
{

}

JDTree::JDTree(float x,float y,float z,int t,float hScale,float vScale)
{
    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;

    this->tag = t;
    this->scale[0] = hScale;
    this->scale[1] = vScale;

    this->radius = hScale+2.0;//a little bit far from tree

}

int JDTree::getTag() const
{
    return this->tag;
}


Vec3 JDTree::getPos() const
{
    return this->pos;
}

float JDTree::getPosX() const
{
    return this->pos[0];
}

float JDTree::getPosY() const
{
    return this->pos[1];
}

float JDTree::getPosZ() const
{
    return this->pos[2];
}

float JDTree::getHScale() const
{
    return this->scale[0];
}

float JDTree::getVScale() const
{
    return this->scale[1];
}


float JDTree::getRadius() const
{
    return this->radius;
}

//to string
QString JDTree::toString()
{
    return "Pos("+ QString::number(this->pos[0]) +","+ QString::number(this->pos[1]) +","+ QString::number(this->pos[2]) +")"
            + "tag " + QString::number(this->tag)
            + "scale("+ QString::number(this->scale[0]) + "," + QString::number(this->scale[1]) + ")";
}
