/**
 *
 *  @file jdterrain.cpp
 *
 *  @brief The class specify jurrassic terrain model, now it is just for testing texture
 *
 *  @author Ren DING
 *  @date 08/08/12.
 *
 */

#include "glheaders.h"
#include "jdterrain.h"
#include "jdUtility.h"
#include "headers.h"

// Cube vertex data
GLfloat terrainVertices[4][3] = {
    { -1.0, 0.0,  1.0 },
    { 1.0,  0.0,  1.0 },
    { 1.0,  0.0, -1.0 },
    { -1.0, 0.0, -1.0 }
};

JDTerrain::JDTerrain(GLfloat width, GLfloat thick, GLfloat height)
{
    this->terrainWidth = width;
    this->terrainThick = thick;
    this->terrainHeight = height;
}

JDTerrain::~JDTerrain()
{
}

//
// Load Texture Map
//
void JDTerrain::loadTextureMap()
{
    QImage img;
    img.load("/Users/rending/Desktop/JurassicDucks/CSIT/mapTexture.png");

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    //Compulsory OpenGL parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //Copy image pixels to GPU
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 img.width(), img.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    createTiles();
}


void JDTerrain::createTiles()
{
    //for testing
    int samples[2] = {1024,1024};

    for(int row = 0; row < samples[0]; row+=256)
    {
        for(int col = 0; col < samples[1]; col+=256)
        {
            jdtiles.append(JDTile(row,col,256,256));
        }
    }
}

//
// draw terrain
//
void JDTerrain::drawTerrain()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texID);

    glPushMatrix();
        //glColor3fv(jdUtility::COLOR_DARK_SALMON);
        glScalef(terrainWidth,terrainThick,terrainHeight);
        glTranslatef(0.0, -1.0, 0.0);
        bool flag = true;
        if(flag)
        {
            glBegin(GL_POLYGON);
                glNormal3f(0, 1, 0);
                glTexCoord2f(0.0, 0.0); glVertex3fv(terrainVertices[0]);
                glTexCoord2f(1.0, 0.0); glVertex3fv(terrainVertices[1]);
                glTexCoord2f(1.0, 1.0); glVertex3fv(terrainVertices[2]);
                glTexCoord2f(0.0, 1.0); glVertex3fv(terrainVertices[3]);
            glEnd();
        } else {
            QVector<JDTile>::iterator jdtilesIter;
            for(jdtilesIter = jdtiles.begin(); jdtilesIter < jdtiles.end(); jdtilesIter++)
            {
                JDTile jdtile = *jdtilesIter;
                jdtile.render();
            }
        }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
