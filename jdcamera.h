/**
 *
 *  @file jcamera.h
 *
 *  @brief The head file of jdcamera.cpp
 *
 *  @author Ren DING
 *  @date 05/08/12.
 *
 */


#ifndef __JDCAMERAH__
#define __JDCAMERAH__


#include "glheaders.h"
#include "Vec3.h"

class JDCamera
{
public:
    GLdouble viewMtx[16];
    Vec3 initEye;
    Vec3 initAt;
    Vec3 initUp;
    Vec3 initAction;//yaw, pitch, roll

    bool turnOn;

public:
    JDCamera( double eyex, double eyey, double eyez,
              double atx, double aty, double atz,
              double upx, double upy, double upz,
              double yaw, double pitch,double roll);
    virtual ~JDCamera();

    //get/set view matrix
    const GLdouble *getViewMtx() const;
    void setViewPoint();
    const Vec3 getEyeMtx() const;

    // moving operations
    void mousemove(int screenPosX, int screenPosY);
    void forward();
    void backward();
    void moveleft();
    void moveright();

    void forwardBackwardRelease();
    void leftRightRelease();

    //turn on/off mouse control
    void mouseSwitch();

    //for bird's eye view
    void orthogonaliseViewMtx();
};

#endif // __JDCAMERAH__
