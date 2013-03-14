/**
 *
 *  @file jdfont.h
 *
 *  @brief The head file of jdfont.cpp
 *
 *  @author Ren DING
 *  @date 23/08/12.
 *
 */

#ifndef __JFONTH__
#define __JFONTH__

#include "headers.h"

class JDFont
{
public:
    JDFont();

    void paint();

protected:
    QBrush background;
    QFont textFont;
    QPen textPen;
};

#endif // __JFONTH__
