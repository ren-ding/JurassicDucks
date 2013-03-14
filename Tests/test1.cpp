#include <iostream>
#include <stdlib.h>
using namespace std;

#define NOTUSED_ELEMENT -1

bool lineOfSightTile(int startRow, int startCol,
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

int main() {
    int startRow = 0,  startCol = 0;
    int endRow = 3, endCol = 2;
    int pathRow[21], pathCol[21];
    int maxPathStep = 21;
    
    if(lineOfSightTile(startRow, startCol,
                       endRow, endCol,
                       pathRow, pathCol,
                       maxPathStep)) {
        for(int i = 0;i < 21;i++) {
            cout<< pathRow[i]<<","<<pathCol[i] << endl;
        }
    }

	return 0;	
}
