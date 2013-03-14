/**
 *
 *  @file jdtext.h
 *
 *  @brief The head file of jdtext.cpp
 *
 *  @author Ren DING
 *  @date 10/09/12.
 *
 */

#ifndef __JDTEXTH__
#define __JDTEXTH__

#include "headers.h"

class JDText
{
protected:
    QVector<QString> messages;

    int textPosX, textPosY;
    int messagesSize;
public:
    JDText(int size);

    //append / replace / clean / get message
    void append(QString str);
    void replace(int index, QString str);
    void clean();
    QVector<QString> getMessages() const;

    //display text
    void displayPlayerHealth(QGLWidget* widget);
    void displayDucksInfo(QGLWidget* widget);
};

#endif // __JDTEXTH__
