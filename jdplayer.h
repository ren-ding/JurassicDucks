/**
 *
 *  @file jdplayer.h
 *
 *  @brief The head file of jdplayer.cpp
 *
 *  @author Ren DING
 *  @date 11/08/12.
 *
 */


#ifndef __JDPLAYERH__
#define __JDPLAYERH__

#include "glheaders.h"
#include "Vec3.h"
class JDucks;

class JDPlayer
{
protected:
    Vec3 position;
    int actionState;
    bool shaded;
    int health;

public:
    JDPlayer(GLfloat posX, GLfloat posY, GLfloat posZ);
    virtual ~JDPlayer();

    //get/set position
    Vec3    getPos() const;
    GLfloat getPosX() const;
    GLfloat getPosY() const;
    GLfloat getPosZ() const;

    void setPosX(GLfloat posX);
    void setPosY(GLfloat posY);
    void setPosZ(GLfloat posZ);

    //set shaded or not
    void setShaded(bool isShaded);

    int getActionState() const; //get current action state
    void stopState();           //set current action state = stop
    void moveState();           //set current action state = move

    //the duck caught the player, therefore, player's health is decreased
    bool killedByDuck();
    //set/get the player's health
    void setHealth(int health);
    int getHealth() const;

    //check if player is catched or not
    bool catchedOrNot(int duckRow, int duckCol);

    //draw the player
    void drawPlayer();
};

#endif // __JDPLAYERH__
