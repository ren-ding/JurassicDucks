/**
 *
 *  @file jduckswidget.cpp
 *
 *  @brief The class provides jurrassic ducks canvas
 *
 *  @author Ren DING
 *  @date 02/08/12.
 *
 */

#include "headers.h"
#include "glheaders.h"

#include "jduck.h"
#include "jducks.h"
#include "jdplayer.h"
#include "jdtree.h"
#include "jdtrees.h"
#include "jdlight.h"

#include "jdUtility.h"
#include "jdalgorithm.h"
#include "jdgpushader.h"
#include "jdfactors.h"

#include "jduckswidget.h"

const float FOVY = 60.0;
const float NEAR = 1.0;
const float FAR = 300.0;
const int DUCK_RANDOM_POSX_BOUNDS = 180;
const int DUCK_RANDOM_POSZ_BOUNDS = 180;

JDucksWidget::JDucksWidget(QWidget *parent)
    : QGLWidget(parent)
{
    //Application exits when window closed
    this->setAttribute(Qt::WA_DeleteOnClose);
    displayDucksInfo = false;

    //set background color
    this->backgroundColor = Vec3(135.0/255.0,206.0/255.0,250.0/255.0);
    this->isDefaultColor = true;

    //skip the first random number
    JDAlgorithm::getRandomNumber(0,80,true);

    //construct and initialize player
    int playerPosX = 0.0, playerPosZ = 60.0;
    this->jdplayer = new JDPlayer(playerPosX, 0.0, playerPosZ);

    //construct ducks and add them to the duck vector
    this->jducks = new JDucks();
    JDuck* tempDuck;

    int numOfDucks = 50;
    for(int i = 0; i < numOfDucks;i++) {
        int duckPosX = JDAlgorithm::getRandomNumber(0,DUCK_RANDOM_POSX_BOUNDS,false);
        int duckPosZ = JDAlgorithm::getRandomNumber(0,DUCK_RANDOM_POSZ_BOUNDS,false);
        tempDuck = new JDuck(duckPosX-DUCK_RANDOM_POSX_BOUNDS/2, 0.0, duckPosZ-DUCK_RANDOM_POSZ_BOUNDS/2);

        //add duck to the ducks set
        this->jducks->addJDuck(tempDuck);
    }

    //construct and initialize map and trees
    jdMap = new JDMap("CSIT");

    //construct and load trees from file
    jdTrees = new JDTrees(*jdMap);

    //construct and initialize light
    this->pLight = new JDLight();
    //construct and initialize text
    this->pText = new JDText(jducks->getDucks().size());

    //construct and initialize camera
    //eyeX, eyeY, eyeZ,
    //atX,  atY,  atZ,
    //upX,  upY,  upZ,
    //yaw, pitch, roll
    personViewCamera = new JDCamera( jdplayer->getPosX(), jdplayer->getPosY() + 2.0, jdplayer->getPosZ(),
                            jdplayer->getPosX(), jdplayer->getPosY() + 2.0, jdplayer->getPosZ()-1.0,
                            0.0, 1.0, 0.0,
                            -JDAlgorithm::PI/2.0, atan(-20.0/150.0), 0.0);

    float birdEyePosX = 0.0;
    float birdEyePosY = 20.0;
    float birdEyePosZ = 140.0;

    birdEyeViewCamera = new JDCamera( birdEyePosX, birdEyePosY, birdEyePosZ,
                                      0.0, 0.0, 0.0,
                                      0.0, birdEyePosZ/sqrt(birdEyePosY*birdEyePosY+birdEyePosZ*birdEyePosZ), -birdEyePosY/sqrt(birdEyePosY*birdEyePosY+birdEyePosZ*birdEyePosZ),
                                      -JDAlgorithm::PI/2.0, atan(-20.0/150.0), 0.0);

    this->pCamera = personViewCamera;
    //set MouseTracking true to capture mouse event even its key is not pressed
    this->setMouseTracking(true);
}

JDucksWidget::~JDucksWidget()
{
    delete jducks;
    delete jdplayer;
    delete jdMap;

    delete personViewCamera;
    delete birdEyeViewCamera;
    delete pCamera;
    delete pLight;
    delete pText;

    jducks = 0;
    jdplayer = 0;
    jdMap = 0;

    pCamera = 0;
    personViewCamera = 0;
    birdEyeViewCamera = 0;
    pLight = 0;
    pText = 0;
}

//
//  get functions
//
 JDCamera* JDucksWidget::getCamera() const
 {
     return this->pCamera;
 }

 JDCamera* JDucksWidget::getPersonViewCamera() const
 {
     return this->personViewCamera;
 }

 JDCamera* JDucksWidget::getBirdEyeViewCamera() const
 {
     return this->birdEyeViewCamera;
 }

 JDText*  JDucksWidget::getText() const
 {
     return this->pText;
 }

JDPlayer* JDucksWidget::getPlayer() const
{
    return this->jdplayer;
}

JDucks* JDucksWidget::getJducks() const
{
    return this->jducks;
}

JDMap* JDucksWidget::getMap() const
{
    return this->jdMap;
}

JDTrees* JDucksWidget::getTrees()const
{
    return this->jdTrees;
}


bool JDucksWidget::getIsDefaultColor() const
{
    return this->isDefaultColor;
}

//set functions
void JDucksWidget::setCamera(JDCamera* updatedCamera)
{
    this->pCamera = updatedCamera;
}


void JDucksWidget::setGpuProgramToWire()
{
    this->gpuProgram = this->wireProgram;
}

void JDucksWidget::setGpuProgramToShade()
{
    this->gpuProgram = this->shaderProgram;
}


void JDucksWidget::willChangeBackgroundColor()
{
    isDefaultColor = false;
}

//turn on/off Ducks' Information display
void JDucksWidget::displayDucksInfoSwitch()
{
    this->displayDucksInfo = !this->displayDucksInfo;
}

//
// initilized draw environment
//
void JDucksWidget::initializeGL()
{
    //black background
    glClearColor(backgroundColor[0],backgroundColor[1],backgroundColor[2],0.0);
    jdUtility::CheckGL("glClearColor");

    //set the limited value for depth
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    //set shade mode
    glShadeModel(GL_SMOOTH);
    //glDepthFunc(GL_LEQUAL);// run depth test for values <= depth set above

    //culling
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);

    //initialize the shader loader
    initShaders();
    //load all models from files
    this->jdMap->load(*jdTrees);
}

//shaders
void JDucksWidget::initShaders()
{
    GPUShader vert, frag;
    //Shader program for standard lighting with texture map
    vert = GpuLoadShader(GL_VERTEX_SHADER,appPath+"std_vert.glsl");
    frag = GpuLoadShader(GL_FRAGMENT_SHADER, appPath+"std_frag.glsl");
    this->shaderProgram = GpuNewProgram(vert, frag);
    //Shader program for wireframe
    vert = GpuLoadShader(GL_VERTEX_SHADER,appPath+"wire_vert.glsl");
    frag = GpuLoadShader(GL_FRAGMENT_SHADER, appPath+"wire_frag.glsl");
    this->wireProgram = GpuNewProgram(vert, frag);
    //Shader program for ducks
    vert = GpuLoadShader(GL_VERTEX_SHADER,appPath+"duck_vert.glsl");
    frag = GpuLoadShader(GL_FRAGMENT_SHADER, appPath+"duck_frag.glsl");
    this->duckProgram = GpuNewProgram(vert, frag);

    this->gpuProgram = this->shaderProgram;
    jdUtility::CheckGL("initShaders");
}

//
//  resize canvas
//
void JDucksWidget::resizeGL(int width, int height)
{
    this->winWidth = width;
    this->winHeight = height;
}

//
//  rendering functions
//

void JDucksWidget::paintGL()
{
    //qDebug()<<"paintGL start";
    glViewport(0, 0, this->winWidth, this->winHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glClearColor(backgroundColor[0],backgroundColor[1],backgroundColor[2],0.0);
    //check if it is a default color
    if(!this->isDefaultColor)
    {
        glClearColor(1.0,0.0,0.0,0.0);
        this->isDefaultColor = true;
    }

    this->setProjection();
    this->setViewPoint();
    GpuUseProgram(gpuProgram);
    this->drawWorld();

    GpuUseProgram(0);
    pText->displayPlayerHealth(this);
    //draw text from QT, turn off gpu shader
    if(displayDucksInfo)
    {
        pText->displayDucksInfo(this);
        GpuUseProgram(gpuProgram);
    }
    //qDebug()<<"paintGL end";
}

void JDucksWidget::setProjection()
{
    GLfloat aspect;

    //Perspective rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspect = (float) this->winWidth/ (float) this->winHeight;
    gluPerspective(FOVY,aspect,NEAR, FAR);
}

void JDucksWidget::setViewPoint()
{
    //gluLookAt( pCamera->initEye[0], pCamera->initEye[1], pCamera->initEye[2],
    //           pCamera->initAt[0], pCamera->initAt[1], pCamera->initAt[2],
    //           pCamera->initUp[0], pCamera->initUp[1], pCamera->initUp[2] );
    this->pCamera->setViewPoint();
}

void JDucksWidget::drawWorld()
{
    //turn on light
    pLight->turnOn();

    //everything have white specular highlights
    //ambient and diffuse materials bound to vertex colour
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

    glPushMatrix();
        jdMap->render();
        GpuUseProgram(this->duckProgram);
        jducks->drawJDucks();
        //the player also use the duck's program, because the player's model is not created
        jdplayer->drawPlayer();
        GpuUseProgram(this->gpuProgram);
    glPopMatrix();

    glDisable( GL_COLOR_MATERIAL );
}
