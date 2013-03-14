/**
 *
 *  @file jducks.cpp
 *
 *  @brief The class provides jurrassic ducks array list
 *
 *  @author Ren DING
 *  @date 05/08/12.
 *
 */

#include "jduck.h"
#include "jducks.h"
#include "jdplayer.h"
#include "jdtrees.h"
#include "jdtext.h"
#include "jdalgorithm.h"
#include "jduckswidget.h"

#include <QVector>


const int FLOCKING = 0;
const int PATTERNMOVEMENT = 1;

const int PATROLLING = 0;
const int CHASING = 1;

const int STOP = 0;
const int MOVE = 1;

const int DUCK_RANDOM_POSX_BOUNDS = 180;
const int DUCK_RANDOM_POSZ_BOUNDS = 180;

JDucks::JDucks()
{
    this->shaded = true;
}

JDucks::~JDucks()
{

}

//set/get functions
void JDucks::setShaded(bool isShaded)
{
    this->shaded = isShaded;
}

//
//  add jduck to duck vector
//
bool JDucks::addJDuck(JDuck* pJduck)
{
    this->duckList.push_back(pJduck);
    return true;
}

//
//  get duckList
//
QVector<JDuck*> JDucks::getDucks() const
{
    return this->duckList;
}

//
//  remove jduck by its index
//
bool JDucks::removeJDuck(int jduckIndex)
{
    if(duckList.size() > 0)
    {
        //should delete pointer here
        this->duckList.remove(jduckIndex);
        return true;
    } else {
        return false;
    }
}

//
// remove jduck by its reference
//
bool JDucks::removeJDuck(JDuck* pJduck)
{
    if(this->duckList.size() > 0)
    {
        int index = this->duckList.indexOf( &(*pJduck) );
        if(index != -1)
            this->duckList.remove(index);
            delete pJduck;
            pJduck = 0;
    }
    return false;
}

//
//flocking movement
//
void JDucks::move(JDTrees* jdtrees, JDText* jdtext,JDPlayer* jdplayer,int movingBehavious,JDucksWidget* canvas)
{
    jdtext->replace(0,"HEALTH: " + QString::number(jdplayer->getHealth()));

    Vec3 playerPos = jdplayer->getPos();
    //iterating the ducks
    QVector<JDuck*>::iterator duckIter;
    int indexIter = 0;
    for(duckIter = this->duckList.begin(); duckIter < this->duckList.end(); duckIter++)
    {
        //pick one duck
        JDuck* jduck = *duckIter;
        Vec3 jduckPos = jduck->getPos();

        //check if the duck catched the player or not
        if(JDAlgorithm::catchedOrNot(playerPos[0],playerPos[2],jduckPos[0],jduckPos[2]))
        {
            qDebug()<<"Caught player!";
            if(jdplayer->killedByDuck()) {
                QMessageBox::information(NULL,"Killed by ducks","Killed by ducks, restart the game");
                jdplayer->setHealth(10);
                //add ten more ducks
                JDuck* tempDuck;

                int numOfDucks = 10;
                for(int i = 0; i < numOfDucks;i++) {
                    int duckPosX = JDAlgorithm::getRandomNumber(0,DUCK_RANDOM_POSX_BOUNDS,false);
                    int duckPosZ = JDAlgorithm::getRandomNumber(0,DUCK_RANDOM_POSZ_BOUNDS,false);
                    tempDuck = new JDuck(duckPosX-DUCK_RANDOM_POSX_BOUNDS/2, 0.0, duckPosZ-DUCK_RANDOM_POSZ_BOUNDS/2);

                    //add duck to the ducks set
                    this->addJDuck(tempDuck);
                }
            }
            this->removeJDuck(jduck);
            canvas->willChangeBackgroundColor();
            continue;
        }

        //check if the duck is out of the map
        jduck->outOfMap();

        if(movingBehavious == FLOCKING)
        {
            //update duck's velocity, orientation etc.
            jduck->update(0.025);

            //set steering force based on flocking algorithm (cohesion, seperation and obstacle avoidance)
            //it also perform the chasing algorithm if the player is within the ducks view area
            jduck->setOtherForce(JDAlgorithm::flocking(jduck,this,jdtrees));

            //chase the player if it is within the duck's view area
            if(JDAlgorithm::seeOrNot(playerPos[0],playerPos[2],jduckPos[0],jduckPos[2]))
            {
                Vec3 tempD = playerPos-jduckPos;
                tempD.Normalise();

                Vec3 tempW = JDAlgorithm::vRotateCoord(-jduck->getOrientation(),tempD);

                int portOrStarboard = 0;
                //the player is in front of the duck
                if(tempW[2] > 0) {
                    //the player is on the portside
                    if(tempW[0] > 0)
                        portOrStarboard = 1;
                    //the player is on the starboardside
                    if(tempW[0] < 0)
                        portOrStarboard = -1;
                }
                jduck->setOtherForce(Vec3(portOrStarboard * 200,0,0));
            }

            //update the ducks' information
            jdtext->replace(indexIter+1,"Position: (" + QString::number(jduckPos[0]) + ","
                                                    + QString::number(jduckPos[2]) + ") "
                                    +"Orientation: "+ QString::number(jduck->getOrientation())
                                    +"Velocity: "+ QString::number(jduck->getFSpeed()));
        }

        if(movingBehavious == PATTERNMOVEMENT)
        {
            jduck->legsUpdate(200);
            if(jdplayer->getActionState() == MOVE)
            {
                //chase the player if it is within the duck's view area
                if( JDAlgorithm::seeOrNot(playerPos[0],playerPos[2],jduckPos[0],jduckPos[2]) )
                {
                    //set the duck's action state = chasing
                    jduck->chase();
                    //re-calculate the ducks chasing path array
                    jduck->setCurrentPathStep(0);

                    if(jduck->calculateChasingPathArray(playerPos[0],playerPos[2]) )
                    {
                        jduck->setPos(jduck->getPathRow()[1],jduck->getPosY(),jduck->getPathCol()[1]);
                        jduck->increaseCurrentPathStep();
                    }
                    else
                    {
                        qWarning()<< "wrong pattern movement calculation";
                        JDAlgorithm::initializePath(jduck->getPathRow(), jduck->getPathCol(),
                                                    jduck->getMaxPathStep());
                        jduck->patrol();
                    }
                }
                else
                {
                    //set the ducks' action state = patrol
                   jduck->patrol();
                   //update the duck's position
                   jduck->updateToNextPosition();
                }
            } else if(jdplayer->getActionState() == STOP){
                //check the duck's action state
                if(jduck->getAction() == CHASING)
                {
                    //the duck is in chasing state
                    int currentStep = jduck->getCurrentPathStep();

                    //still chasing, update duck's position, go to next step
                    if(currentStep+1 < jduck->getMaxPathStep())
                    {
                        jduck->updateToNextPosition();
                    }
                    else
                    {
                        qWarning() <<"Exception in timerEvent!";
                    }
                }
                else if (jduck->getAction() == PATROLLING)
                {
                    //the duck is in patrol state, pattern movement
                    //the duck does not have patrolling array
                    if(!jduck->getHasPatrolArray())
                       jduck->calculatePatternMovement();

                    //update the duck's position
                    jduck->updateToNextPosition();
                }
            }

            //update the ducks' information
            jdtext->replace(indexIter+1,"Position: (" + QString::number(jduckPos[0]) + ","
                                                    + QString::number(jduckPos[2]) + ") "
                                    +"Orientation: "+ QString::number(jduck->getOrientation()));
        }
        indexIter++;
    }
}

//
//first time, calculating the ducks chasing path array in pattern movement behavious
//
void JDucks::patternMovementfirstCal(Vec3 playerPos)
{
    //iterating the ducks
    QVector<JDuck*>::iterator duckIter;
    for(duckIter = duckList.begin(); duckIter < duckList.end(); duckIter++)
    {
        JDuck* jduck = *duckIter;
        //ducks's (postionX,positionZ) in 3D world coordinate system
        Vec3 jduckPos = jduck->getPos();
        //check if player is in the duck's chasing area
        if(abs(playerPos[0] - jduckPos[0]) <= JDAlgorithm::PATROL_THRESHOLD
           || abs(playerPos[2] - jduckPos[2]) <= JDAlgorithm::PATROL_THRESHOLD )
        {
            //ducks' action state change to chasing state,
            //calculating the duck's chasing path array
            jduck->chase();
            jduck->calculateChasingPathArray(playerPos[0], playerPos[2]);
        }
        else
        {
            //ducks' action state change to patrolling state,
            //calculating the duck's pattern movement path array
            jduck->patrol();
            jduck->calculatePatternMovement();
        }
    }
}

//
//  draw ducks
//
void JDucks::drawJDucks()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glEnable(GL_LIGHTING);
    if(this->shaded)
    {
        glDisable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    glPushMatrix();
        QVector<JDuck*>::iterator duckIter;
        for(duckIter = this->duckList.begin(); duckIter < this->duckList.end(); duckIter++)
            (*duckIter)->drawJDuck();
    glPopMatrix();
    glPopAttrib();
}

