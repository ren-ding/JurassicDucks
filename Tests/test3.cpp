#include <iostream>
#include <stdlib.h>
using namespace std;

//initialize path array
void initializePath(int pathRow[], int pathCol[],
                                 int maxPathStep)
{
    for(int i = 0; i < maxPathStep;i++)
    {
        pathRow[i] = -1;
        pathCol[i] = -1;
    }
}

//build path
bool buildPath(int startRow, int startCol,
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

void normalize(int pathRow[], int pathCol[],
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


void showPath(int pathRow[], int pathCol[],int maxPathStep)
{
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
        cout<< pathRow[i]<<","<<pathCol[i]<<endl;
    }
}

int main() {
    int startRow = 4, startCol = 2;
    int pathRow[200], pathCol[200];
    int maxPathStep = 200;
    initializePath(pathRow,pathCol,maxPathStep);
    
    buildPath(startRow, startCol, 4, 11,
              pathRow, pathCol,maxPathStep);
    //showPath(pathRow, pathCol,maxPathStep);
    
    buildPath(4, 11, 2, 24,
              pathRow, pathCol,maxPathStep);
    //showPath(pathRow, pathCol,maxPathStep);
    
    buildPath(2, 24, 13, 17,
              pathRow, pathCol,maxPathStep);
    //showPath(pathRow, pathCol,maxPathStep);
    
    buildPath(13, 17, startRow, startCol,
              pathRow, pathCol,maxPathStep);
    
    showPath(pathRow, pathCol,maxPathStep);
    
    normalize(pathRow, pathCol,maxPathStep);
    //showPath(pathRow, pathCol,maxPathStep);
	return 0;	
}
