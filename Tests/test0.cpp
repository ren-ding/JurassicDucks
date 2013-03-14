#include <iostream>
#include <stdlib.h>
using namespace std;

bool lineOfSightTile(int startRow, int startCol,
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
    for(curStep = 0; curStep < maxPathStep; curStep++)
    {
        pathRow[curStep] = -1;
        pathCol[curStep] = -1;
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
        //assign the step to the path step array
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

int main() {
    int startRow = 0,  startCol = 0;
    int endRow = 5, endCol = 20;
    int pathRow[40], pathCol[40];
    int maxPathStep = 40;
    
    if(lineOfSightTile(startRow, startCol,
                       endRow, endCol,
                       pathRow, pathCol,
                       maxPathStep)) {
        for(int i = 0;i < 40;i++) {
            cout<< pathRow[i]<<","<<pathCol[i] << endl;
        }
    }

	return 0;	
}
