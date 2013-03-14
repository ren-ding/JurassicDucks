#include <iostream>
#include <stdlib.h>
using namespace std;

bool lineOfSightTile(int startRow, int startCol,
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
    
    nextStep[0] = -1;
    nextStep[1] = -1;
    
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

int main() {
    int endRow = 5, endCol = 20;
    int nextStep[2] = {0,0};
    
    while(!lineOfSightTile(nextStep[0], nextStep[1],
                           endRow, endCol,
                           nextStep)){
        cout<< nextStep[0]<<","<<nextStep[1] << endl;
    }

	return 0;	
}
