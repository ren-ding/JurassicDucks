/**
 *
 *  @file jdobstacles.cpp
 *
 *  @brief The class is just for testing obstacle avoidance
 *
 *  @author Ren DING
 *  @date 23/09/12.
 *
 */

#include "jdobstacle.h"
#include "jdobstacles.h"

JDObstacles::JDObstacles()
{
}

JDObstacles::~JDObstacles()
{

}

//
//  add jdobstacle to jdobstacle vector
//
bool JDObstacles::addJDObstacle(JDObstacle* jdobstacle)
{
    obstacleList.push_back(jdobstacle);
    return true;
}

QVector<JDObstacle*> JDObstacles::getJDObstacles() const
{
    return obstacleList;
}


//
//  remove jdobstacle by its index
//
bool JDObstacles::removeJDObstacle(int jdobstacleIndex)
{
    if(obstacleList.size() > 0)
    {
        //should delete pointer here
        obstacleList.remove(jdobstacleIndex);
        return true;
    }

    return false;
}


//
// remove jdobstacle by its reference
//
bool JDObstacles::removeJDObstacle(JDObstacle* jdobstacle)
{
    if(obstacleList.size() > 0)
    {
        int index = obstacleList.indexOf( &(*jdobstacle) );
        if(index != -1)
            obstacleList.remove(index);
            delete jdobstacle;
            jdobstacle = 0;
    }
    return false;
}

//
// draw obstacles
//
void JDObstacles::drawJDObstacles()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
        QVector<JDObstacle*>::iterator jdobstacleIter;
        for(jdobstacleIter = obstacleList.begin(); jdobstacleIter < obstacleList.end(); jdobstacleIter++)
            (*jdobstacleIter)->drawJDObstacle();
    glPopMatrix();
    glPopAttrib();
}
