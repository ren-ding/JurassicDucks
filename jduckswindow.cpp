/**
 *
 *  @file jduckswindow.cpp
 *
 *  @brief The class provides main window
 *
 *  @author Ren DING
 *  @date 03/08/12.
 *
 */

#include "jduckswindow.h"
#include "jduckswidget.h"
#include "jdfactors.h"
#include "jduck.h"
#include "jducks.h"
#include "jdplayer.h"
#include "jdflockdialog.h"
#include "jdalgorithm.h"
#include "headers.h"
#include "Vec3.h"

const double FRAMEPERSEC = 60.0;
const double CALCULATEPERSEC = 5.0;
const int FLOCKING = 0;
const int PATTERNMOVEMENT = 1;

float seperationFactor = 0;
float viewRadiusFactor = 0;
float steeringForceFactor = 0;
float visibilityFactor = 0;

QString appPath = QString();

JDucksWindow::JDucksWindow(QWidget * parent)
    :QMainWindow(parent)
{
    appPath = QCoreApplication::applicationDirPath();
    //qDebug() << QCoreApplication::applicationDirPath();
    //On Mac OS, path is like ../JurassicDucks.app/Contents/MacOS
    //therefore, just remove these
    #if defined(__APPLE__)
    appPath.remove(appPath.length()-32,32);
    #else
    appPath.append("/");
    #endif
    //set control variables
    this->isFullScreen = false;
    this->movingBehavious = 0;

    //create menu
    this->createMenu();
    //initialized the canvas, put it in the main window
    this->pCanvas = new JDucksWidget(this);

    this->setCentralWidget(pCanvas);

    //set MouseTracking true to capture mouse event even its key is not pressed
    this->setMouseTracking(true);

    //kick off timer
    this->updateSpinner = this->startTimer((int)(1000/FRAMEPERSEC));
    this->calculateSpinner = this->startTimer((int)(1000/CALCULATEPERSEC));

    //key table
    //"W","A","S","D","V","M"
    keyPressTable.insert("KEY_W",false);
    keyPressTable.insert("KEY_A",false);
    keyPressTable.insert("KEY_S",false);
    keyPressTable.insert("KEY_D",false);
    keyPressTable.insert("KEY_V",false);
    keyPressTable.insert("KEY_M",false);

    loadJDdata();
}

JDucksWindow::~JDucksWindow()
{
    delete pCanvas;
    pCanvas = 0;
}


//load data from jddata when program starting
void JDucksWindow::loadJDdata()
{
    //qDebug()<<appPath;
    QMap<QString, float> factorMap = readMap(appPath+"jddata");
    seperationFactor = factorMap.value("seperationFactor");
    viewRadiusFactor = factorMap.value("viewRadiusFactor");
    steeringForceFactor = factorMap.value("steeringForceFactor");
    visibilityFactor = factorMap.value("visibilityFactor");

    //qDebug()<<seperationFactor <<viewRadiusFactor<<steeringForceFactor<<visibilityFactor;
}

//
//  create menu for main GUI
//
void JDucksWindow::createMenu()
{
    QMenuBar * menuBar;
    QMenu *    menu;
    QAction *  item;

    //set menubar, menu and menu items with QT
    menuBar = this->menuBar();

    //first menu, Jurassic Ducks
    menu    = menuBar->addMenu(tr("Jurassic Ducks"));

    item    = new QAction(tr("Full Screen"),this);
    menu->addAction(item);
    connect(item,SIGNAL(triggered()),this,SLOT(fullScreen()));

    item    = new QAction(tr("Display ducks' Information"),this);
    menu->addAction(item);
    connect(item,SIGNAL(triggered()),this,SLOT(ducksInfo()));

    item    = new QAction(tr("About"),this);
    menu->addAction(item);
    connect(item,SIGNAL(triggered()),this,SLOT(about()));

    item    = new QAction(tr("Exit"),this);
    menu->addAction(item);
    connect(item,SIGNAL(triggered()),this,SLOT(close()));

    //second menu, chasing and evading algorithm
    menu    = menuBar->addMenu(tr("Moving behavious"));

    item    = new QAction(tr("Flocking"),this);
    menu->addAction(item);
    connect(item,SIGNAL(triggered()),this,SLOT(flocking()));

    item    = new QAction(tr("Pattern Movement"),this);
    menu->addAction(item);
    connect(item,SIGNAL(triggered()),this,SLOT(patternMovement()));


    //third menu, Factor setting
    menu    = menuBar->addMenu(tr("Factor setting"));

    item    = new QAction(tr("Set Flock Factor"),this);
    menu->addAction(item);
    connect(item,SIGNAL(triggered()),this,SLOT(factorSetting()));

    //fourth menu, Viewing options for display
    menu    = menuBar->addMenu(tr("Viewing options"));

    item    = new QAction(tr("Wireframe view"),this);
    menu->addAction(item);
    connect(item,SIGNAL(triggered()),this,SLOT(wireframe()));

    item    = new QAction(tr("Lit and textured"),this);
    menu->addAction(item);
    connect(item,SIGNAL(triggered()),this,SLOT(texturedframe()));
}

//
// set configuration
//
void JDucksWindow::about()
{
    //pop out description box
    QMessageBox::information(NULL,
                             "About Jurassic Juck",
                             "Ren Ding, u5111810, CSIT ANU master student\nSupervisor: Mr. Hugh Fisher\n");
}

//
// turn to full screen
//
void JDucksWindow::fullScreen()
{
    isFullScreen = true;
    this->showFullScreen();
}

void JDucksWindow::ducksInfo()
{
    pCanvas->displayDucksInfoSwitch();
}

void JDucksWindow::flocking()
{
    this->movingBehavious = FLOCKING;
}

void JDucksWindow::patternMovement()
{
    if(this->movingBehavious != PATTERNMOVEMENT) {
        this->movingBehavious = PATTERNMOVEMENT;
        this->pCanvas->getJducks()->patternMovementfirstCal(this->pCanvas->getPlayer()->getPos());
    }
}

void JDucksWindow::wireframe()
{
    pCanvas->setGpuProgramToWire();

    pCanvas->getMap()->setShaded(false);
    pCanvas->getJducks()->setShaded(false);
    pCanvas->getPlayer()->setShaded(false);
}

void JDucksWindow::texturedframe()
{
    pCanvas->setGpuProgramToShade();

    pCanvas->getMap()->setShaded(true);
    pCanvas->getJducks()->setShaded(true);
    pCanvas->getPlayer()->setShaded(true);
}

//
// GUI controls to adjust AI flocking parameters
//
void JDucksWindow::factorSetting()
{
    JDFlockDialog* flockingDialog = new JDFlockDialog(this,appPath + "jddata");
    flockingDialog->show();
}

//
// window events
//

// key press event
void JDucksWindow::keyPressEvent(QKeyEvent * evt)
{
    //qDebug() <<"keyPressEvent";
    if(evt->key() == Qt::Key_Escape)
        this->close();
    else if(evt->key() == Qt::Key_W)
        keyPressTable["KEY_W"] = true;
    else if(evt->key() == Qt::Key_S)
        keyPressTable["KEY_S"] = true;
    else if(evt->key() == Qt::Key_A)
        keyPressTable["KEY_A"] = true;
    else if(evt->key() == Qt::Key_D)
        keyPressTable["KEY_D"] = true;
    else if(evt->key() == Qt::Key_M)
        keyPressTable["KEY_M"] = true;
    else if(evt->key() == Qt::Key_V)
        keyPressTable["KEY_V"] = true;
    else
        //cannot handle, pass along
        QMainWindow::keyPressEvent(evt);
}

//key release event
void JDucksWindow::keyReleaseEvent(QKeyEvent *evt)
{
    //qDebug() <<"keyReleaseEvent";
    if(evt->key() == Qt::Key_W)
        keyPressTable["KEY_W"] = false;
    else if(evt->key() == Qt::Key_S)
        keyPressTable["KEY_S"] = false;
    else if(evt->key() == Qt::Key_A)
        keyPressTable["KEY_A"] = false;
    else if(evt->key() == Qt::Key_D)
        keyPressTable["KEY_D"] = false;
    else if(evt->key() == Qt::Key_M) {
        pCanvas->getCamera()->mouseSwitch();
        keyPressTable["KEY_M"] = false;
    } else if(evt->key() == Qt::Key_V)
        keyPressTable["KEY_V"] = false;
    else
        //cannot handle, pass along
        QMainWindow::keyReleaseEvent(evt);
}

//mouse move event
void JDucksWindow::mouseMoveEvent(QMouseEvent * evt)
{
    //get x and y
    int mx = evt->x();
    int my = evt->y();
    pCanvas->getCamera()->mousemove(mx, my);
}

//
//  timer event, for chasing and evading
//
void JDucksWindow::timerEvent(QTimerEvent * evt)
{
    if (evt->timerId() == updateSpinner)
    {
        this->update();

        //check key press table
        if( this->keyPressTable["KEY_V"] )
            pCanvas->setCamera(pCanvas->getBirdEyeViewCamera());
        else
        {
            pCanvas->setCamera(pCanvas->getPersonViewCamera());

            if( this->keyPressTable["KEY_W"] ||
                this->keyPressTable["KEY_A"] ||
                this->keyPressTable["KEY_S"] ||
                this->keyPressTable["KEY_D"]) {
                    pCanvas->getPlayer()->moveState();
                    //reset player's position
                    //playerPosX = eyeX
                    //playerPosZ = eyeZ
                    pCanvas->getPlayer()->setPosX(pCanvas->getPersonViewCamera()->getEyeMtx()[0]);
                    pCanvas->getPlayer()->setPosZ(pCanvas->getPersonViewCamera()->getEyeMtx()[2]);
            } else {
                    pCanvas->getPlayer()->stopState();
            }

            if( this->keyPressTable["KEY_W"] )
                pCanvas->getPersonViewCamera()->forward();
            if( this->keyPressTable["KEY_S"] )
                pCanvas->getPersonViewCamera()->backward();
            if(!this->keyPressTable["KEY_W"] && !this->keyPressTable["KEY_S"])
                pCanvas->getPersonViewCamera()->forwardBackwardRelease();

            if( this->keyPressTable["KEY_A"] )
                pCanvas->getPersonViewCamera()->moveleft();
            if( this->keyPressTable["KEY_D"] )
                pCanvas->getPersonViewCamera()->moveright();
            if( !this->keyPressTable["KEY_A"] && !this->keyPressTable["KEY_D"])
                pCanvas->getPersonViewCamera()->leftRightRelease();
        }
    } else {
        // cannot handle, pass along
        QMainWindow::timerEvent(evt);
    }

    if (evt->timerId() == calculateSpinner)
    {
        switch(this->movingBehavious) {
            case FLOCKING:
                //flocking
                pCanvas->getJducks()->move(pCanvas->getTrees(),
                                           pCanvas->getText(),
                                           pCanvas->getPlayer(),
                                           FLOCKING,
                                           this->pCanvas);
                break;
            case PATTERNMOVEMENT:
                //pattern movement 
                pCanvas->getJducks()->move(pCanvas->getTrees(),
                                           pCanvas->getText(),
                                           pCanvas->getPlayer(),
                                           PATTERNMOVEMENT,
                                           this->pCanvas);
                break;
        }
    }
}
