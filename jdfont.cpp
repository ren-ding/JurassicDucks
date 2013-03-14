/**
 *
 *  @file jdfont.cpp
 *
 *  @brief The class provide 2d text print
 *
 *  @author Ren DING
 *  @date 05/08/12.
 *
 */

#include "jdfont.h"

JDFont::JDFont()
{
    background = QBrush(QColor(64, 32, 64));
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
}

void JDFont::paint(QPainter *painter, QPaintEvent *event)
{
    //painter->fillRect(event->rect(), background);
    painter->translate(100, 100);
    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, "Qt");
}
