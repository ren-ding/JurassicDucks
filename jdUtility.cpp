/**
 *
 *  @file glUtility.cpp
 *
 *  @brief The class implements utility functions for jurassicDucks
 *
 *  @author Ren DING 
 *  @date 26/07/12.
 *
 */

#include "jdUtility.h"
#include "glheaders.h"
#include "jduckswindow.h"
#include "headers.h"

//
//initialized the main window
//
bool jdUtility::InitGLWindow(QMainWindow* pMainWindow,
                      int width, int height,
                      bool isFullScreen)
{
    //set window title, translate text depend on language surport
    pMainWindow->setWindowTitle(QObject::tr("Jurassic Ducks"));
    //resize window
    pMainWindow->resize(width,height);
    if (isFullScreen)
        pMainWindow->showFullScreen();
    
    return true;
}

//
//  check does the device install OpenGL
//
bool jdUtility::CheckGLExist()
{
    if(!QGLFormat::hasOpenGL())
    {
        throw std::runtime_error("No OpenGL");
    }

    return true;
}

void jdUtility::CheckGL(QString location)
{
    int  err = glGetError();
    if (err != GL_NO_ERROR) {
        qDebug() <<"OpenGL error(" + location + "):"+ (char*) gluErrorString(err);
        exit(0);
    }
}
