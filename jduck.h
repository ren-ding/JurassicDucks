/**
 *
 *  @file jduck.h
 *
 *  @brief The head file of jduck.cpp
 *
 *  @author Ren DING
 *  @date 05/08/12.
 *
 */

#ifndef __JDUCKH__
#define __JDUCKH__

#include "glheaders.h"
#include "Vec3.h"

class JDuck
{
protected:
    Vec3 position;          // duck's position
    GLfloat color[4];       // duck's color

    int actionState;        // duck's action state

    //chasing path array
    int pathRow[255];
    int pathCol[255];

    int maxPathStep;        // max path finding step (finding ability)
    int currentPathStep;    // current path step

    //true, first time chasing
    //false, on the contrary
    bool firstTimeChasing;

    //true, it already calculated the patrol path array
    //false, have not calculated the patrol path array
    bool hasPatrolArray;

    //variables for physicall simulated environments
    //velocity
    Vec3 velocity;          // velocity vector in world coordinate
    float fSpeed;           // magnitude of the velocity in world coordinate
    Vec3 velocityAngular;   // angular velocity in local coordinate

    float orientation;      // orientation

    //forces
    Vec3 force;             // total force
    float thrustForce;      // magnitude of the thrust force
    Vec3 moment;            // total moment (torque) on body
    Vec3 pThrust;           // port side thrust force (left)
    Vec3 sThrust;           // starbord side thrust force (right)
    float fMass;            // total mass (constant)
    float fInertia;			// mass moment of inertia in body coordinates (constant)
    Vec3 otherForce;        // other forces(steering force from flocking function)
    //Vec3 velocityLocal;   // velocity in local coordinate(wind or something)

    //for updating duck's leg
    int legSwing;
    int step;

public:
    JDuck(float x = 0, float y = 0,float z = 0);
    virtual ~JDuck();

    //get/set position
    void setPos(float x, float y,float z);
    float getPosX() const;
    float getPosY() const;
    float getPosZ() const;
    Vec3 getPos() const;

    //set/get velocity vector
    void setVelocity(float x, float y,float z);
    Vec3 getVelocity() const;

    //get speed
    float getFSpeed();

    //set /get orientation
    void setOrientation(float orien);
    float getOrientation() const;

    //set/get force
    void setForce(float x, float y,float z);
    Vec3 getForce() const;

    //set/get otherforce
    void setOtherForce(float x, float y,float z);
    void setOtherForce(Vec3 oForce);
    Vec3 getOtherForce() const;

    //changing action state
    void patrol();
    void chase();

    //get action state
    int getAction() const;

    //get path array, can be revised
    int* getPathRow();
    int* getPathCol();

    //get maxPath Step
    int getMaxPathStep() const;

    //set/get currentPathStep
    int getCurrentPathStep()const;
    void setCurrentPathStep(int curStep);
    void increaseCurrentPathStep();
    void decreaseCurrentPathStep();

    //set/get first time chasing
    bool getFirstTimeChasing()const;
    void setFirstTimeChasing(bool isFirstTimeChasing);

    //set/get hasPatrolArray
    bool getHasPatrolArray() const;
    void setHasPatrolArray(bool hasbuiltPatrolArray);

    //calculate the pattern movement pathArray
    void calculatePatternMovement();
    //calculate the ducks chasing path array
    bool calculateChasingPathArray(int playerRow, int playerPosCol);

    //update duck's position to the next position in path array
    void updateToNextPosition();

    //set thrust force
    void setThrusters(bool p, bool s, double f);
    // Calculate forces and moments
    void calculateForcesMoments();
    //update position, velocity, orientation, force
    void update(double deltaTime);
    void legsUpdate(double deltaTime);
    //detect if the duck run out of the map
    bool outOfMap();

    //draw duck
    void leftLeg_draw();
    void rightLeg_draw();
    void body_draw();
    void drawJDuck();
};

#endif // __JDUCKH__
