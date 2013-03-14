/**
 *
 *  @file jduckswindow.h
 *
 *  @brief The head file of jduckswindow.cpp
 *
 *  @author Ren DING
 *  @date 03/08/12.
 *
 */

#ifndef __JDUCKSWINDOWH__
#define __JDUCKSWINDOWH__

#include <QMainWindow>
#include <QMap>
class JDucksWidget;
class JDFont;

class JDucksWindow : public QMainWindow
{
    Q_OBJECT

protected:
    JDucksWidget* pCanvas;

    // control variables
    bool isFullScreen;
    int movingBehavious;

    //timer
    int updateSpinner;
    int calculateSpinner;

    //build the window
    void createMenu();

    //overrides
    void keyPressEvent(QKeyEvent* evt);
    void keyReleaseEvent(QKeyEvent *evt);
    void mouseMoveEvent(QMouseEvent * evt);
    void timerEvent(QTimerEvent *evt);

    QMap<QString, bool> keyPressTable;

protected slots:
    void about();
    void fullScreen();
    void ducksInfo();
    void patternMovement();
    void flocking();
    void factorSetting();
    void wireframe();
    void texturedframe();


public:
    JDucksWindow(QWidget * parent);
    virtual ~JDucksWindow();

    //load data from jddata when program start
    void loadJDdata();
};


#endif // __JDUCKSWINDOWH__
