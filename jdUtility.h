/**
 *
 *  @file glUtility.h
 *
 *  @brief The head file of glUtility.cpp
 *
 *  @author Ren DING 
 *  @date 26/07/12.
 *
 */

#ifndef __JDUTILITYH__
#define __JDUTILITYH__

#include "glheaders.h"
#include <QMainWindow>

namespace jdUtility
{
    //
    // Init
    //
    bool InitGLWindow(QMainWindow* mainWindow,
                      int width, int height,
                      bool isFullScreen =false);
    //check does the device install OpenGL
    bool CheckGLExist();
    //check OpenGL function
    void CheckGL(QString location);

    //
    //Look at Matrix structure
    //
    struct LookAtMatrix
    {
        GLfloat _eyeX, _eyeY, _eyeZ;
        GLfloat _origX, _origY, _origZ;
        GLfloat _upX, _upY, _upZ;

        LookAtMatrix(){}
        LookAtMatrix(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
                     GLfloat origX, GLfloat origY, GLfloat origZ,
                     GLfloat upX, GLfloat upY, GLfloat upZ)
        {
            _eyeX   = eyeX; _eyeY   = eyeY;   _eyeZ = eyeZ;
            _origX  = origX;_origY  = origY; _origZ = origZ;
            _upX    = upX;  _upY    = upY;   _upZ   = upZ;
        }
    };

    const GLfloat COLOR_WHITE[3] = {1.0, 1.0, 1.0} ;
    const GLfloat COLOR_RED[3] = {1.0, 0.0, 0.0} ;
    const GLfloat COLOR_GREEN[3] = {0.0, 1.0, 0.0} ;
    const GLfloat COLOR_BLUE[3] = {0.0, 0.0, 1.0} ;
    const GLfloat COLOR_IVORY[3] = {205.0/255.0, 205.0/255.0, 193.0/255.0} ;
    const GLfloat COLOR_DARK_SALMON[3] = {233.0/255.0, 150.0/255.0, 122.0/255.0} ;
}


#endif //__JDUTILITYH__
