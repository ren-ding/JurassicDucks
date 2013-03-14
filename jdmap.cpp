/**
 *
 *  @file jdmap.cpp
 *
 *  @brief The class provide map loader,
 *  which is based on Mr Hugh Fisher's map loader (python version)
 *
 *  @author Ren DING
 *  @date 06/10/12.
 *
 */

#include "jdmap.h"
#include "Vec4.h"
#include "glheaders.h"
#include "jdUtility.h"
#include "jdfactors.h"

JDMap::JDMap(QString dirN)
{
    this->dirName = dirN;
    this->scale = 0.2;
    this->bounds[0] = 0;
    this->bounds[1] = 0;
    this->samples[0] = 0;
    this->samples[1] = 0;

    this->shaded = true;

    this->TypeInfo.insert( "TypeInfoLine00_None",      Vec4(0.0, 0.0, 0.0, 0.0)    ); // 0
    this->TypeInfo.insert( "TypeInfoLine01_",          Vec4(1.0, 1.0, 1.0, 1.0)    ); // 1
    this->TypeInfo.insert( "TypeInfoLine02_Water",     Vec4(0.0, 0.0, 1.0, 1.0)    ); // 2
    this->TypeInfo.insert( "TypeInfoLine03_",          Vec4(1.0, 1.0, 1.0, 1.0)    ); // 3
    this->TypeInfo.insert( "TypeInfoLine04_Tree",      Vec4(0.0, 0.5, 0.25, 1.0)   ); // 4
    this->TypeInfo.insert( "TypeInfoLine05_",          Vec4(1.0, 1.0, 1.0, 1.0)    ); // 5
    this->TypeInfo.insert( "TypeInfoLine06_Bush",      Vec4(0.22, 0.71, 0.29, 1.0) ); // 6
    this->TypeInfo.insert( "TypeInfoLine07_",          Vec4(1.0, 1.0, 1.0, 1.0)    ); // 7
    this->TypeInfo.insert( "TypeInfoLine08_Dirt",      Vec4(0.55, 0.38, 0.22, 1.0) ); // 8
    this->TypeInfo.insert( "TypeInfoLine09_",          Vec4(1.0, 1.0, 1.0, 1.0)    ); // 9
    this->TypeInfo.insert( "TypeInfoLine10_Grass",    Vec4(0.0, 1.0, 0.0, 1.0)    ); // 10
    this->TypeInfo.insert( "TypeInfoLine11_Rubble",   Vec4(0.25, 0.25, 0.25, 1.0) ); // 11
    this->TypeInfo.insert( "TypeInfoLine12_",         Vec4(1.0, 1.0, 1.0, 1.0)    ); // 12
    this->TypeInfo.insert( "TypeInfoLine13_Concrete", Vec4(0.78, 0.70, 0.59, 1.0) ); // 13
    this->TypeInfo.insert( "TypeInfoLine14_Building", Vec4(0.46, 0.30, 0.14, 1.0) ); // 14
    this->TypeInfo.insert( "TypeInfoLine15_Road",     Vec4(0.0, 0.0, 0.0, 1.0)    ); // 15
}

void JDMap::load(JDTrees jdtrees)
{
    this->jdtrees = jdtrees;
    loadTypeData();
    loadTextureMap();
    createTiles();
    loadTrees();
}

int JDMap::colorToType(int red)
{
    //  Convert pixel 0..255 value into type code 0..15, allowing
    //  for value to be a bit off either way.
    return int(floor((red + 7) / 16));
}

Vec4 JDMap::typeColor(int t)
{
    return TypeInfo.values()[t];
}

//
//set/get functions
//
QString JDMap::getDirName() const
{
    return this->dirName;
}
float JDMap::getScale() const
{
    return this->scale;
}

float* JDMap::getBounds()
{
    return this->bounds;
}

float* JDMap::getSamples()
{
    return this->samples;
}


void JDMap::setShaded(bool isShaded)
{
    this->shaded = isShaded;
}


int JDMap::getTypeColor(int index)
{
    return this->typeData[index];
}

void JDMap::loadTypeData()
{
    QImage img;

    img.load(appPath+dirName+ "/mapType.png");

    int countNum = this->TypeInfo.size();
    int* count = new int[countNum];

    for(int i = 0;i < countNum; i++) {
        count[i] = 0;
    }

    qDebug()<<"image height:" << img.height();
    qDebug()<<"image width:" << img.width();

    for(int y = 0;y < img.height(); y++)
    {
        //int row[img.width()];
        for(int x = 0; x < img.width(); x++)
        {
            //Only use gray scale value, all components should be equal
            int t = colorToType(qRed(img.pixel(x,y)));
            //for debugging
            if(t >countNum || t < 0)
                qDebug()<<"out of boundary";
            count[t] +=1;
            this->typeData.append(t);
        }
    }
    this->samples[0] = img.width();
    this->samples[1] = img.height();

    this->bounds[0] = img.width() * this->scale;
    this->bounds[1] = img.height() * this->scale;

    //help with debugging
    qDebug()<<"Map dimensions:(" + QString::number(this->bounds[0]) +"," + QString::number(this->bounds[1])+")";
    qDebug()<<"Map types:";
    QList<QString> keys = TypeInfo.keys();
    for(int i = 0;i < countNum; i++) {
        qDebug()<< keys[i] << count[i];
    }

}

void JDMap::loadTextureMap()
{
    QImage img;
    img.load(appPath+dirName+"/mapTexture.png");

    qDebug()<<"depth:"<<img.depth();

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    jdUtility::CheckGL("glBindTexture");
    //Compulsory OpenGL parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //Copy image pixels to GPU
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //QImage RGBA is BGRA
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 img.width(), img.height(), 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, img.bits());
    jdUtility::CheckGL("glTexImage2D");
    qDebug()<<"Loaded texture map";
}


// Break map into smaller chunks. Can make rendering more
// efficient, but these days with modern GPUs it isn't
// really worth doing.
void JDMap::createTiles()
{
    //take off, because large array cannot be created in tile render function
    //jdtiles.append(JDTile(*this,0,0,1024,1024));
    for(int row = 0; row < samples[0]; row+=256)
    {
        for(int col = 0; col < samples[1]; col+=256)
        {
            if(row == 768 && col == 768)
                //jdtiles.append(JDTile(*this,row,col,256,256));
                jdtiles.append(JDTile(*this,row,col,256,256,0));
            else if(row == 768)
                //jdtiles.append(JDTile(*this,row,col,256,257));
                jdtiles.append(JDTile(*this,row,col,256,256,1));
            else if(col == 768)
                //jdtiles.append(JDTile(*this,row,col,257,256));
                jdtiles.append(JDTile(*this,row,col,256,256,2));
            else
                //jdtiles.append(JDTile(*this,row,col,257,257));
                jdtiles.append(JDTile(*this,row,col,256,256,3));
        }
    }

    qDebug()<<"Created tiles";
}

void JDMap::loadTrees()
{
    jdtrees.loadFromFile(this->dirName);
    qDebug()<<"Load Trees";
}

void JDMap::render()
{
    //Render either as wireframe or lit & shaded.
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //qDebug()<<"isShaded:"<<shaded<<"texID"<<texID;
    if(this->shaded && this->texID > 0)
    {
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, texID);
        jdUtility::CheckGL("glBindTexture");
    }
    else if(this->shaded)
    {
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        jdUtility::CheckGL("glPolygonMode GL_FILL");
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        jdUtility::CheckGL("glPolygonMode GL_LINE");
    }

    glPushMatrix();
    //Map coords start from corner. Shift to centre of map
    glTranslatef(-this->bounds[0]/2, -1, -this->bounds[1]/2);

    //Just render all the bits
    //qDebug()<<"tile size" <<jdtiles.size();
    QVector<JDTile>::iterator jdtilesIter;
    for(jdtilesIter = jdtiles.begin(); jdtilesIter < jdtiles.end(); jdtilesIter++)
    {
        JDTile jdtile = *jdtilesIter;
        jdtile.render();
    }

    jdtrees.render(this->shaded);

    glPopMatrix();
    glPopClientAttrib();
    glPopAttrib();
}
