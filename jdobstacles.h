/**
 *
 *  @file jdobstacles.h
 *
 *  @brief The head file of jdobstacles.cpp
 *
 *  @author Ren DING
 *  @date 23/09/12.
 *
 */


#ifndef __JDOBSTACLESH__
#define __JDOBSTACLESH__

#include <QVector>
class JDObstacle;

class JDObstacles
{
protected:
   QVector<JDObstacle*> obstacleList;

public:
    JDObstacles();
    virtual ~JDObstacles();

    bool addJDObstacle(JDObstacle* jdobstacle);
    QVector<JDObstacle*> getJDObstacles() const;

    bool removeJDObstacle(int jdobstacleIndex);
    bool removeJDObstacle(JDObstacle* jdobstacle);

    void drawJDObstacles();
};

#endif // __JDOBSTACLESH__
