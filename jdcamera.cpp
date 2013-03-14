/**
 *
 *  @file jdcamera.cpp
 *
 *  @brief The class provides view control
 *
 *  @author Ren DING
 *  @date 05/08/12.
 *
 */

#include "jdcamera.h"
#include "headers.h"

const double PI = 3.1415926535897932384626433832795;
const double DEG = 180.f / PI;
const double RAD = PI / 180.f;

static float axs = 0.f, axf = 0.f, ay = 0.f, azs = 0.f, azf = 0.f;
static float step = .5f, angle = 0.0f, anglestep = 2.0f;

JDCamera::JDCamera(double eyex, double eyey, double eyez,
                   double atx, double aty, double atz,
                   double upx, double upy, double upz,
                   double yaw, double pitch,double roll)
{
    this->initEye[0] = eyex;
    this->initEye[1] = eyey;
    this->initEye[2] = eyez;

    this->initAt[0] = atx;
    this->initAt[1] = aty;
    this->initAt[2] = atz;

    this->initUp[0] = upx;
    initUp[1] = upy;
    initUp[2] = upz;

    this->initAction[0] = yaw;
    this->initAction[1] = pitch;
    this->initAction[2] = roll;

    //reset mouse
    this->turnOn = true;
}

JDCamera::~JDCamera()
{

}

const GLdouble * JDCamera::getViewMtx() const
{
    return viewMtx;
}

void JDCamera::setViewPoint()
{

    glGetDoublev( GL_MODELVIEW_MATRIX, viewMtx );

    initEye[0]+=axs + axf;  initEye[1]+=ay; initEye[2]+=azs + azf;
    initAt[0] +=axs + axf;  initAt[1] +=ay; initAt[2] +=azs + azf;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( initEye[0], initEye[1], initEye[2],
               initAt[0], initAt[1], initAt[2],
               initUp[0], initUp[1], initUp[2] );
}


const Vec3 JDCamera::getEyeMtx() const
{
    return initEye;
}

//
// mouse event control
//

void JDCamera::mousemove(int screenPosX, int screenPosY) {
    static int prevScreenPosX = screenPosX, prevScreenPosY = screenPosY;
    static int deltaX, deltaY;
    static float radspeed = 0.1f*RAD;

    //calculate the move distance
    if(this->turnOn)
    {
        deltaX = screenPosX - prevScreenPosX;
        deltaY = screenPosY - prevScreenPosY;
    }
    else
    {// reset and turn off the mouse move event
        prevScreenPosX = screenPosX;
        prevScreenPosY = screenPosY;
        deltaX = deltaY = 0;
        return;
    }

    //save current position to previous position
    prevScreenPosX = screenPosX;
    prevScreenPosY = screenPosY;

    //change camera variables to make mouse move control it
    initAction[0] += deltaX * radspeed;

    if (initAction[0]>=PI*2.0f || initAction[0]<=-PI*2.0f) {
        initAction[0] = 0.0f;
    }
    initAction[1] -= deltaY * radspeed;
    if (initAction[1] >= 85.f*RAD) {
        initAction[1] = 85.f*RAD;
    }else if(initAction[1] <= -85.f*RAD) {
        initAction[1] = -85.f*RAD;
    }

    float cosyaw = cos(initAction[0]);
    float sinyaw = sin(initAction[0]);
    float sinpitch = sin(initAction[1]);
    float cospitch = cos(initAction[1]);
/*
    initAt[0] = initEye[0] + cosyaw;
    initAt[2] = initEye[2] + sinyaw;
    initAt[1] = initEye[1];
*/
    initAt[0] = initEye[0] + cospitch*cosyaw;
    initAt[2] = initEye[2] + cospitch*sinyaw;
    initAt[1] = initEye[1] + sinpitch;

    setViewPoint();
}



//
// key event control
//

void JDCamera::forward()
{
    axf = cos(initAction[0])*step;
    azf = sin(initAction[0])*step;
}

void JDCamera::backward()
{
    axf =-cos(initAction[0])*step;
    azf =-sin(initAction[0])*step;
}

void JDCamera::moveleft()
{
    axs = sin(initAction[0])*step;
    azs =-cos(initAction[0])*step;
}

void JDCamera::moveright()
{
    axs =-sin(initAction[0])*step;
    azs = cos(initAction[0])*step;
}

void JDCamera::forwardBackwardRelease()
{
    axf = 0.0;
    azf = 0.0;
}

void JDCamera::leftRightRelease()
{
    axs = 0.0;
    azs = 0.0;
}

//turn on/off mouse control
void JDCamera::mouseSwitch()
{
    turnOn = !turnOn;
}

//orthogonalise view matrix
void JDCamera::orthogonaliseViewMtx()
{
    Vec3 xAxis( viewMtx[0], viewMtx[1], viewMtx[2] );
    Vec3 yAxis( viewMtx[4], viewMtx[5], viewMtx[6] );
    Vec3 zAxis( viewMtx[8], viewMtx[9], viewMtx[10] );

    // Gram-Schmidt orthogonalisation
    normalise( yAxis );
    zAxis = zAxis - dot( zAxis, yAxis ) * yAxis;
    normalise( zAxis );
    xAxis = xAxis - dot( xAxis, yAxis ) * yAxis
    - dot( xAxis, zAxis ) * zAxis;
    normalise( xAxis );

    viewMtx[0] = xAxis[0]; viewMtx[4] = yAxis[0]; viewMtx[8] = zAxis[0];
    viewMtx[1] = xAxis[1]; viewMtx[5] = yAxis[1]; viewMtx[9] = zAxis[1];
    viewMtx[2] = xAxis[2]; viewMtx[6] = yAxis[2]; viewMtx[10] = zAxis[2];
}

