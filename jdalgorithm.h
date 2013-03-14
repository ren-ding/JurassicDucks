/**
 *
 *  @file jdalgorithm.h
 *
 *  @brief The head file of jdalgorithm.cpp
 *
 *  @author Ren DING
 *  @date 10/08/12.
 *
 */

#ifndef __JDALGORITHMH__
#define __JDALGORITHMH__

#include "jduck.h"
#include "jducks.h"
#include "jdtrees.h"

namespace JDAlgorithm
{
    //If the distance between player and ducks is greater than this value,
    //ducks will keep patroling
    const int PATROL_THRESHOLD = 10;

    //NotUsedElement indicates which element in the path array are not used
    const int NOTUSED_ELEMENT = -1;

    //Pi
    const double PI = 3.1415926535897932384626433832795;

    // angle conversion tool function
    float	DegreesToRadians(float deg);
    float	RadiansToDegrees(float rad);

    // random generator tool function
    int getRandomNumber(int min, int max, bool seed);

    //tanslate vector from global coordinate to local coordinate
    //global(x,-,z) -> local(x,-,z)
    Vec3 vRotateCoord( float orientation, Vec3 global);

    // basic chasing and evading, line of sight tile
    bool basicChasingEvading(int startRow, int startCol,
                             int endRow, int endCol,
                             int pathRow[], int pathCol[],
                             int maxPathStep);

    bool lineOfSightTile(int startRow, int startCol,
                         int endRow, int endCol,
                         int pathRow[], int pathCol[],
                         int maxPathStep);

    bool catchedOrNot(int playerRow, int playerCol,
                      int duckRow, int duckCol);

    bool seeOrNot(int playerRow, int playerCol,
                  int duckRow, int duckCol);
/*
    bool lineOfSightTile(int startRow, int startCol,
                         int endRow, int endCol,
                         int nextStep[2]);
*/
    //pattern movement
    void initializePath(int pathRow[], int pathCol[],
                        int maxPathStep);

    bool buildPath(int startRow, int startCol,
                   int endRow,  int endCol,
                   int pathRow[], int pathCol[],
                   int maxPathStep);

    void normalize(int pathRow[], int pathCol[],
                   int maxPathStep);

    //Flocking algorithms
    Vec3 flocking(JDuck* jduck,JDucks* jducks,JDTrees* jdtrees);

}

#endif // __JDALGORITHMH__
