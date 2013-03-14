/**
 *
 *  @file jdalgorithm.cpp
 *
 *  @brief The class implements AI algorithms functions for chasing and evading
 *
 *  @author Ren DING
 *  @date 10/08/12.
 *
 */

#include "jdalgorithm.h"
#include "headers.h"
#include "jdfactors.h"
#include "Vec3.h"

//
//  angle conversion functions
//
float	JDAlgorithm::DegreesToRadians(float deg)
{
    return deg * PI / 180.0f;
}

float	JDAlgorithm::RadiansToDegrees(float rad)
{
    return rad * 180.0f / PI;
}

//
// random generator tool function
//
int JDAlgorithm::getRandomNumber(int min, int max, bool seed)
{
    int	number;

    if(seed)
        srand( (unsigned)time( NULL ) );

    number = ( ((abs(rand())%(max-min+1))+min) );

    if(number>max)  number = max;

    if(number<min)  number = min;

    return number;
}

//
//tanslate vector from local coordinate to global coordinate
//
Vec3 JDAlgorithm::vRotateCoord( float orientation, Vec3 global)
{
    float	x,z;
    x = global[0] * cos(DegreesToRadians(-orientation)) + global[2] * sin(DegreesToRadians(-orientation));
    z = -global[0] * sin(DegreesToRadians(-orientation)) + global[2] * cos(DegreesToRadians(-orientation));

    return Vec3( x, global[1], z);
}

//
//  basic chasing and evading algorithm, just perform increment and decrement on positions
//
bool JDAlgorithm::basicChasingEvading(int startRow, int startCol,
                                      int endRow, int endCol,
                                      int pathRow[], int pathCol[],
                                      int maxPathStep)
{
    // does find or not
    bool find = false;

    //build path to target
    int nextRow = startRow;
    int nextCol = startCol;

    int deltaRow = endRow - startRow;
    int deltaCol = endCol - startCol;

    int stepCol, stepRow;
    int curStep;

    //path array initialization
    //(-1,-1) indicates which element in the path array are not used
    for(curStep = 0; curStep < maxPathStep; curStep++)
    {
        pathRow[curStep] = NOTUSED_ELEMENT;
        pathCol[curStep] = NOTUSED_ELEMENT;
    }

    //back to start step
    curStep = 0;

    //path direction clculation
    if(deltaRow < 0)
        stepRow = -1;
    else
        stepRow = 1;

    if(deltaCol < 0)
        stepCol = -1;
    else
        stepCol = 1;

    while(!find)
    {
        if(curStep > maxPathStep)
            break;
        //assign the first step to the path step array
        pathRow[curStep] = nextRow;
        pathCol[curStep] = nextCol;
        curStep++;

        //get the target
        if(deltaRow == 0 && deltaCol ==0)
        {
            find = true;
        }
        else if(deltaRow == 0)
        {
            nextCol += stepCol;
        }
        else if(deltaCol == 0)
        {
            nextRow += stepRow;
        }
        else
        {
            nextRow += stepRow;
            nextCol += stepCol;
        }

        deltaRow = endRow - nextRow;
        deltaCol = endCol - nextCol;
    }

    return find;
}

//
//line-of-sight chasing and evading algorithm in tiled environment (Bresenham's line algorithm)
//
bool JDAlgorithm::lineOfSightTile(int startRow, int startCol,
                                  int endRow, int endCol,
                                  int pathRow[], int pathCol[],
                                  int maxPathStep)
{
    //build path to target
    int nextRow = startRow;
    int nextCol = startCol;

    int deltaRow = endRow - startRow;
    int deltaCol = endCol - startCol;

    int stepCol, stepRow;
    int curStep;
    int fraction;

    //path array initialization
    //(-1,-1) indicates which element in the path array are not used
    for(curStep = 0; curStep < maxPathStep; curStep++)
    {
        pathRow[curStep] = NOTUSED_ELEMENT;
        pathCol[curStep] = NOTUSED_ELEMENT;
    }

    //back to start step
    curStep = 0;

    //path direction calculation
    if(deltaRow < 0)
        stepRow = -1;
    else
        stepRow = 1;

    if(deltaCol < 0)
        stepCol = -1;
    else
        stepCol = 1;

    deltaRow = abs(deltaRow*2);
    deltaCol = abs(deltaCol*2);

    //assign the first step to the path step array
    pathRow[curStep] = nextRow;
    pathCol[curStep] = nextCol;
    curStep++;

    //Bresenham algorithm
    if(deltaCol > deltaRow)
    {
        fraction = deltaRow*2 - deltaCol;
        while (nextCol != endCol)
        {
            //current step greater than max path step,
            //failed to find within the limited path step
            if(curStep > maxPathStep)
                return false;

            if(fraction > 0) // column axis is the longest
            {
                nextRow = nextRow + stepRow;
                fraction -= deltaCol;
            }
            nextCol = nextCol + stepCol;
            fraction += deltaRow;

            //record the path
            pathRow[curStep] = nextRow;
            pathCol[curStep] = nextCol;
            curStep++;
        }
    } else {// deltaCol < deltaRow
        fraction = deltaCol*2 - deltaRow;
        while (nextRow != endRow)
        {
            //current step greater than max path step,
            //failed to find within the limited path step
            if(curStep > maxPathStep)
                return false;

            if(fraction >= 0) //// row axis is the longest
            {
                nextCol = nextCol + stepCol;
                fraction -= deltaRow;
            }
            nextRow = nextRow + stepRow;
            fraction += deltaCol;

            //record the path
            pathRow[curStep] = nextRow;
            pathCol[curStep] = nextCol;
            curStep++;
        }
    }

    //find the path with the max path steps
    return true;
}

//
// set minimal Distance to test if the duck cathced the player or not
//
bool JDAlgorithm::catchedOrNot(int playerRow, int playerCol,
                               int duckRow, int duckCol)
{
    int deltaRow = abs(playerRow-duckRow);
    int deltaCol = abs(playerCol-duckCol);

    int minimalDistanceJustice = 2;
    if(deltaRow < minimalDistanceJustice && deltaCol < minimalDistanceJustice)
        return true;
    else
        return false;
}


//
// set minimal Distance to test if the duck see the player or not
//
bool JDAlgorithm::seeOrNot(int playerRow, int playerCol,
                           int duckRow, int duckCol)
{
    int deltaRow = abs(playerRow-duckRow);
    int deltaCol = abs(playerCol-duckCol);

    if(deltaRow < viewRadiusFactor && deltaCol < viewRadiusFactor)
        return true;
    else
        return false;
}

//
//  calcualte next step by line-of-sight algorithm
//
/*
bool JDAlgorithm::lineOfSightTile(int startRow, int startCol,
                                  int endRow, int endCol,
                                  int nextStep[2])
{
    //have found target
    if(startRow == endRow && startCol == endCol)
        return true;

    //build path to target
    int deltaRow = endRow - startRow;
    int deltaCol = endCol - startCol;

    int stepCol, stepRow;

    nextStep[0] = NOTUSED_ELEMENT;
    nextStep[1] = NOTUSED_ELEMENT;

    //path direction clculation
    if(deltaRow < 0)
        stepRow = -1;
    else
        stepRow = 1;

    if(deltaCol < 0)
        stepCol = -1;
    else
        stepCol = 1;

    deltaRow = abs(deltaRow*2);
    deltaCol = abs(deltaCol*2);

    //Bresenham algorithm
    if(deltaCol > deltaRow)
    {
        if(deltaRow*2 - deltaCol > 0) // column axis is the longest
        {
            nextStep[0] = startRow + stepRow;
        } else {
            nextStep[0] = startRow;
        }
        nextStep[1] = startCol + stepCol;
    }
    else// deltaCol < deltaRow
    {
        if(deltaCol*2 - deltaRow >= 0) // row axis is the longest
        {
            nextStep[1] = startCol + stepCol;
        } else {
            nextStep[1] = startCol;
        }
        nextStep[0] = startRow + stepRow;
    }

    return false;
}

*/

//
//pattern movement
//

//initialize path array
void JDAlgorithm::initializePath(int pathRow[], int pathCol[],
                                 int maxPathStep)
{
    ////(NOTUSED_ELEMENT,NOTUSED_ELEMENT) indicates which element in the path array are not used
    for(int i = 0; i < maxPathStep;i++)
    {
        pathRow[i] = NOTUSED_ELEMENT;
        pathCol[i] = NOTUSED_ELEMENT;
    }
}

//build path
bool JDAlgorithm::buildPath(int startRow, int startCol,
                            int endRow,  int endCol,
                            int pathRow[], int pathCol[],
                            int maxPathStep)
{
    // does find or not
    bool find = false;

    //build path to target
    int nextRow = startRow;
    int nextCol = startCol;

    int deltaRow = endRow - startRow;
    int deltaCol = endCol - startCol;

    int stepCol, stepRow;
    int curStep;
    int fraction;

    //find the current step
    for(int i = 0; i < maxPathStep; i++)
    {
        if( (pathRow[i] == -1) && (pathCol[i] == -1) )
        {
            curStep = i;
            break;
        }
    }

    //path direction calculation
    if(deltaRow < 0)
        stepRow = -1;
    else
        stepRow = 1;

    if(deltaCol < 0)
        stepCol = -1;
    else
        stepCol = 1;

    deltaRow = abs(deltaRow*2);
    deltaCol = abs(deltaCol*2);

    //assign the first step to the path step array
    pathRow[curStep] = nextRow;
    pathCol[curStep] = nextCol;
    curStep++;

    //Bresenham algorithm
    if(deltaCol > deltaRow)
    {
        fraction = deltaRow*2 - deltaCol;
        while (nextCol != endCol)
        {
            //current step greater than max path step, failed to find
            if(curStep > maxPathStep)
                return find;

            if(fraction > 0) // column axis is the longest
            {
                nextRow = nextRow + stepRow;
                fraction -= deltaCol;
            }
            nextCol = nextCol + stepCol;
            fraction += deltaRow;

            //record the path
            pathRow[curStep] = nextRow;
            pathCol[curStep] = nextCol;
            curStep++;
        }
    } else {// deltaCol < deltaRow
        fraction = deltaCol*2 - deltaRow;
        while (nextRow != endRow)
        {
            //current step greater than max path step, failed to find
            if(curStep > maxPathStep)
                return find;

            if(fraction >= 0) //// row axis is the longest
            {
                nextCol = nextCol + stepCol;
                fraction -= deltaRow;
            }
            nextRow = nextRow + stepRow;
            fraction += deltaCol;

            //record the path
            pathRow[curStep] = nextRow;
            pathCol[curStep] = nextCol;
            curStep++;
        }
    }

    return true;
}

void JDAlgorithm::normalize(int pathRow[], int pathCol[],
                            int maxPathStep)
{
    int rowZero = pathRow[0];
    int colZero = pathCol[0];

    int pathSize = maxPathStep;
    //calculate the path size
    for(int i = 0; i < maxPathStep;i++)
    {
        if((pathRow[i] == -1) && (pathCol[i] == -1))
        {
            pathSize = i - 1;
            break;
        }
    }

    //normalize path array
    for(int i = 0; i <= pathSize;i++)
    {
        pathRow[i] -= rowZero;
        pathCol[i] -= colZero;
    }
}

//
//  Flocking algorithm
//

Vec3 JDAlgorithm::flocking(JDuck* jduck,JDucks* jducks,JDTrees* jdtrees)
{
    //qDebug()<<seperationFactor<<viewRadiusFactor<<steeringForceFactor<<visibilityFactor;
    int  numOfNeighbors;            //number of neighbors
    Vec3 avePosition;               //average position vector
    Vec3 aveVelocity;               //average velocity vector
    Vec3 steeringForce;             //steering force
    Vec3 pSteeringForce;            //point of application of steeringForce

    Vec3 tempDifPos,tempW;          //for calculating neighbors
    Vec3 tempU, tempV;              //for performing flocking rules

    double portOrStarboard;         //multiple variable.+1 or -1
    bool inView;                    //is in the view

    //start to flock
    numOfNeighbors = 0;

    avePosition[0] = 0;
    avePosition[1] = 0;
    avePosition[2] = 0;

    aveVelocity[0] = 0;
    aveVelocity[1] = 0;
    aveVelocity[2] = 0;

    steeringForce[0] = 0;
    steeringForce[1] = 0;
    steeringForce[2] = 0;

    pSteeringForce[0] = 0;
    pSteeringForce[1] = 1 / 2.0;//duck length / 2

    //calculate neighbors and related factors
    QVector<JDuck*> duckList = jducks->getDucks();
    QVector<JDuck*>::iterator duckIter;
    for(duckIter = duckList.begin(); duckIter < duckList.end(); duckIter++)
    {
        JDuck* pDuck = *duckIter;
        if(pDuck != jduck)
        {
            inView = false;
            tempDifPos = pDuck->getPos() - jduck->getPos();
            //tanslate vector from global coordinate to local coordinate
            tempW = vRotateCoord(-jduck->getOrientation(),tempDifPos);

            if(tempW[2] > 0 && tempDifPos.magnitude() < viewRadiusFactor)
            {
                inView = true;
                numOfNeighbors++;
            }

            //seperation rule
            if(inView)
            {
                if(tempDifPos.magnitude() <= seperationFactor)
                {
                    if(tempW[0] < 0) portOrStarboard = 1;
                    if(tempW[0] > 0) portOrStarboard = -1;
                    if(tempW[0] == 0) portOrStarboard = 0;

                    steeringForce[0] += portOrStarboard * seperationFactor / tempDifPos.magnitude();
                }

            }
        }
    }

    //QMessageBox::information(NULL, "keyReleaseEvent",QString::number(steeringForce[0]));

    //int flockingType = 0;
    //cohesion rule
    if(numOfNeighbors > 0)//||flockingType = 0
    {
        avePosition = avePosition / numOfNeighbors;

        tempV = jduck->getVelocity();
        tempV.Normalise();

        tempU = avePosition - jduck->getPos();
        tempU.Normalise();

        tempW = vRotateCoord(-jduck->getOrientation(),tempU);
        if(tempW[0] < 0) portOrStarboard = -1;
        if(tempW[0] > 0) portOrStarboard = 1;
        if(tempW[0] == 0) portOrStarboard = 0;

        if(fabs( tempV.dotProduct(tempU) ) < 1.0)
            steeringForce[0] += portOrStarboard * steeringForceFactor * acos(tempV.dotProduct(tempU)) / PI;
    }

    //alignment rule
    if(numOfNeighbors > 0)//||flockingType = 1
    {

        aveVelocity = aveVelocity/numOfNeighbors;

        tempU = aveVelocity;

        tempU.Normalise();

        tempV = jduck->getVelocity();
        tempV.Normalise();

        tempW = vRotateCoord(jduck->getOrientation(),tempU);

        if(tempW[0] < 0) portOrStarboard = -1;
        if(tempW[0] > 0) portOrStarboard = 1;
        if(tempW[0] == 0) portOrStarboard = 0;


        if(fabs( tempV.dotProduct(tempU) ) < 1.0)
            steeringForce[0] += portOrStarboard * steeringForceFactor * acos(tempV.dotProduct(tempU)) / PI;

    }

    //collision avoidance
    Vec3 tempA; //Vector, which is from duck to obstacle center
    Vec3 tempP; //Vector, which is from duck to its view direction
    Vec3 tempB; //Vector, which starts obstacle center and is perpendicular to tempP

    QVector<JDTree> trees = jdtrees->getTrees();
    QVector<JDTree>::iterator jdtreesIter;
    for(jdtreesIter = trees.begin(); jdtreesIter < trees.end(); jdtreesIter++)
    {
        JDTree tree = *jdtreesIter;

        tempU = jduck->getVelocity();
        tempU.Normalise();
        tempV = tempU * visibilityFactor;

        tempA = tree.getPos() - jduck->getPos();
        tempP = (tempA.dotProduct(tempU)) * tempU;
        tempB = tempP - tempA;

        if((tempB.magnitude() < tree.getRadius()) && (tempP.magnitude() < tempV.magnitude()))
        {

            //steering away
            tempW = vRotateCoord(-jduck->getOrientation(), tempA);
            tempW.Normalise();
            if(tempW[0] < 0) portOrStarboard = 1;
            if(tempW[0] > 0) portOrStarboard = -1;
            if(tempW[0] == 0) portOrStarboard = 1;

            steeringForce[0] += portOrStarboard * steeringForceFactor * visibilityFactor / tempA.magnitude();
        }
    }
    return steeringForce;
}
