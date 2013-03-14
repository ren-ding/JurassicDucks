/**
 *
 *  @file jdtext.cpp
 *
 *  @brief The class is for rendering 2d text on the widget.
 *
 *  @author Ren DING
 *  @date 10/09/12.
 *
 */

#include "jdtext.h"
#include "jdUtility.h"

JDText::JDText(int size)
{
    this->messagesSize = size;
    this->textPosX = 50;
    this->textPosY = 50;
    messages = QVector<QString>(size);
}

//append / replace / clean / get message
void JDText::append(QString str)
{
    this->messages.append(str);
}

void JDText::replace(int index, QString str)
{
    if(index >=0 && index < this->messages.size())
    {
        this->messages.replace(index,str);
    }
}

void JDText::clean()
{
    this->messages.clear();
}

QVector<QString> JDText::getMessages() const
{
    return this->messages;
}

void JDText::displayPlayerHealth(QGLWidget* widget)
{
    glPushMatrix();
        glColor3fv(jdUtility::COLOR_RED);
        QVector<QString>::iterator messagesIter;
        QString message = *messages.begin();
        widget->renderText(this->textPosX,this->textPosY,message);
    glPopMatrix();
}

//display text
void JDText::displayDucksInfo(QGLWidget* widget)
{
    glPushMatrix();
        glColor3fv(jdUtility::COLOR_RED);
        QVector<QString>::iterator messagesIter;
        this->textPosY += 15;
        for(messagesIter = messages.begin()+1; messagesIter < messages.end(); messagesIter++)
        {
            QString message = *messagesIter;
            widget->renderText(this->textPosX,this->textPosY,message);
            this->textPosY += 15;
        }

        this->textPosX = 50;
        this->textPosY = 50;
    glPopMatrix();
}
