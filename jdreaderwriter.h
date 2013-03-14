/**
 *
 *  @file jdreaderwriter.h
 *
 *  @brief The head file of jdreaderwriter.cpp
 *
 *  @author Ren DING
 *  @date 23/09/12.
 *
 */


#ifndef __JDREADERWRITERH__
#define __JDREADERWRITERH__

#include "headers.h"

extern "C" {
    QMap<QString,float> readMap(QString filename);
    void writeMap(QMap<QString, float> map, QString filename);
}

#endif // __JDREADERWRITERH__
