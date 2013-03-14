#ifndef _GLHEADERS_
#define _GLHEADERS_

// Written by Hugh Fisher reivsed by Ren Ding

/* For programs built with CMake, but easily adapted.
   include this file instead of gl.h, glu.h, etc */

#define GL_GLEXT_PROTOTYPES
#if defined(WIN32)
    /* Only need enough of Windows API for OpenGL API */
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    /* MSWin without GLee is a world of pain */
    #include "GLee.h"
    /* GLee includes gl.h but not glu */
    #include <GL/glu.h>
    /* Assume GLUT is copied locally, not system wide */
    #include "glut.h"
#elif defined(__APPLE__)
    /* Futards changed the header file directory */
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <Glut/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glext.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

#endif
