/**
 *
 *  @file jdplayer.cpp
 *
 *  @brief The class specify jurrassic player model
 *
 *  @author Ren DING
 *  @date 11/08/12.
 *
 */

#include "jdplayer.h"
#include "jducks.h"
#include "jduck.h"
#include "headers.h"
#include "jdalgorithm.h"
#include "jdUtility.h"


const int STOP = 0;
const int MOVE = 1;

//player vertex data
static GLfloat playerVertices[8][3] = {
  { -1.0, -1.0,  1.0 }, // 0 left bottom front
  {  1.0, -1.0,  1.0 }, // 1 right bottom front
  {  1.0,  1.0,  1.0 }, // 2 right top front
  { -1.0,  1.0,  1.0 }, // 3 left top front
  { -1.0, -1.0, -1.0 }, // 4 left bottom rear
  {  1.0, -1.0, -1.0 }, // 5 right bottom rear
  {  1.0,  1.0, -1.0 }, // 6 right top rear
  { -1.0,  1.0, -1.0 }  // 7 left top rear
};

//player face vertex
static GLuint playerFaces[] = {
    0, 1, 2, 3, // front
    1, 5, 6, 2, // right
    5, 4, 7, 6, // rear
    4, 0, 3, 7, // left
    3, 2, 6, 7, // top
    4, 5, 1, 0  // bottom
};


static GLfloat playerNormals[6][3] = {
    { 0, 0, 1 },
    { 1, 0, 0 },
    { 0, 0, -1},
    { -1, 0, 0},
    { 0, 1, 0 },
    { 0, -1, 0}
};

JDPlayer::JDPlayer(GLfloat x, GLfloat y, GLfloat z)
{
    this->shaded = true;

    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;

    this->actionState = STOP;
    this->health = 10;
}

JDPlayer::~JDPlayer()
{

}

//get/set function
Vec3 JDPlayer::getPos() const
{
    return this->position;
}


GLfloat JDPlayer::getPosX() const
{
    return this->position[0];
}

GLfloat JDPlayer::getPosY() const
{
    return this->position[1];
}

GLfloat JDPlayer::getPosZ() const
{
    return this->position[2];
}

void JDPlayer::setPosX(GLfloat x)
{
    this->position[0] = x;
}

void JDPlayer::setPosY(GLfloat y)
{
    this->position[1] = y;
}

void JDPlayer::setPosZ(GLfloat z)
{
    this->position[2] = z;
}

//set shaded or not
void JDPlayer::setShaded(bool isShaded)
{
    this->shaded = isShaded;
}


//action state control funciton
void JDPlayer::stopState()
{
    this->actionState = STOP;
}

void JDPlayer::moveState()
{
    this->actionState = MOVE;
}

int JDPlayer::getActionState() const
{
    return this->actionState;
}

//
//the duck caught the player, therefore, player's health is decreased
//return true, if the player's health is 0(killed by the duck)
//
bool JDPlayer::killedByDuck()
{
    if(this->health == 1) {
        this->health--;
        return true;
    }

    this->health--;
    return false;
}

//
//set/get the player's health
//

void JDPlayer::setHealth(int health)
{
    this->health = health;
}

int JDPlayer::getHealth() const
{
    return this->health;
}

//
//check if player is catched
//
bool JDPlayer::catchedOrNot(int duckRow, int duckCol)
{
    return JDAlgorithm::catchedOrNot(this->getPosX(),this->getPosZ(),
                                     duckRow,duckCol);
}

void JDPlayer::drawPlayer()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    if(this->shaded)
    {
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    glPushMatrix();
        glColor3fv(jdUtility::COLOR_BLUE);
        glTranslatef(this->position[0], this->position[1], this->position[2]);
        // Draw cube in traditional OpenGL style
        glBegin(GL_QUADS);
        for (int i = 0; i < 6 * 4; i++)
        {
            glVertex3fv(playerVertices[playerFaces[i]]);
            glNormal3fv(playerNormals[i / 4]);
        }
        glEnd();
    glPopMatrix();
    glPopAttrib();
}
