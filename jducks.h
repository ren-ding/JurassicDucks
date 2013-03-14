/**
 *
 *  @file jducks.h
 *
 *  @brief The head file of jducks.cpp
 *
 *  @author Ren DING
 *  @date 05/08/12.
 *
 */

#ifndef __JDUCKSH__
#define __JDUCKSH__

#include <QVector>
class JDuck;
class JDPlayer;
class JDTrees;
class JDText;
class Vec3;
class JDucksWidget;

class JDucks
{
protected:
   QVector<JDuck*> duckList;
   bool shaded;

public:
    JDucks();
    virtual ~JDucks();

    //set/get functions
    void setShaded(bool isShaded);

    //add / remove ducks
    bool addJDuck(JDuck* jduck);
    QVector<JDuck*> getDucks() const;
    bool removeJDuck(int jduckIndex);
    bool removeJDuck(JDuck* jduck);

    //move functions
    void move(JDTrees* jdtrees, JDText* jdtext,JDPlayer* jdplayer,int movingBehavious,JDucksWidget* canvas);
    void patternMovementfirstCal(Vec3 playerPos);

    //draw jucks
    void drawJDucks();
};

#endif // __JDUCKSH__
