/**
 *
 *  @file jduckswidget.h
 *
 *  @brief The head file of jduckswidget.cpp
 *
 *  @author Ren DING
 *  @date 02/08/12.
 *
 */

#ifndef __JDUCKSWIDGETH__
#define __JDUCKSWIDGETH__

#include <QtOpenGL/QGLWidget>

#include "jducks.h"
#include "jdcamera.h"
#include "jdplayer.h"
#include "jdtrees.h"
#include "jdlight.h"
#include "jdtext.h"
#include "jdgpushader.h"
#include "jdmap.h"


class JDucksWidget : public QGLWidget
{
    Q_OBJECT
    
protected:
    int winWidth, winHeight;
    bool displayDucksInfo;
    Vec3 backgroundColor;
    bool isDefaultColor;

    JDucks *    jducks;
    JDPlayer *  jdplayer;
    JDMap *     jdMap;
    JDTrees *   jdTrees;

    JDCamera *  pCamera;
    JDCamera *  personViewCamera;
    JDCamera *  birdEyeViewCamera;
    JDLight *   pLight;
    JDText *    pText;

    //shaders
    GPUProgram shaderProgram;
    GPUProgram wireProgram;
    GPUProgram duckProgram;
    GPUProgram gpuProgram;

    //overrides
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    //rendering
    virtual void setProjection();
    virtual void setViewPoint();
    virtual void drawWorld();

    //shaders
    void initShaders();
public:
    JDucksWidget(QWidget *parent);
    virtual ~JDucksWidget();

    //get funcitons
    JDCamera* getCamera() const;
    JDCamera* getPersonViewCamera() const;
    JDCamera* getBirdEyeViewCamera() const;
    JDText *  getText() const;
    JDPlayer* getPlayer() const;
    JDucks*   getJducks() const;
    JDMap*    getMap() const;
    JDTrees*  getTrees()const;

    bool getIsDefaultColor() const;

    //set functions
    void setCamera(JDCamera* updatedCamera);
    void setGpuProgramToWire();
    void setGpuProgramToShade();

    void willChangeBackgroundColor();

    //turn on/off Ducks' Information display
    void displayDucksInfoSwitch();
};

#endif // __JDUCKSWIDGETH__
