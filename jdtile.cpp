/**
 *
 *  @file jdtile.cpp
 *
 *  @brief The class break map into smaller triangle meshes.
 *
 *  @author Ren DING
 *  @date 07/10/12.
 *
 */

#include "jdtile.h"
#include "jdmap.h"
#include "glheaders.h"
#include "jdUtility.h"

JDTile::JDTile()
{

}

///////////////////////
//     //     //     //
//  3  //  3  //  1  //
//     //     //     //
///////////////////////
//     //     //     //
//  3  //  3  //  1  //
//     //     //     //
///////////////////////
//     //     //     //
//  2  //  2  //  0  //
//     //     //     //
///////////////////////
JDTile::JDTile(JDMap jdmap,int i, int j, int w, int h, int whichPart)
{
    if(whichPart == 0)
        ;
    else if(whichPart == 1)
        h++;
    else if(whichPart == 2)
        w++;
    else if(whichPart == 3){
        h++;
        w++;
    }

    //Create from map with pixel origin (i, j) and W x H pixels
    for(int outer = j; outer < j+h; outer++)
    {
        for(int inner = i; inner < i+w; inner++)
        {
            GLfloat x = inner * jdmap.getScale();
            GLfloat y = 0;
            GLfloat z = outer * jdmap.getScale();
            this->verts.append(x);
            this->verts.append(y);
            this->verts.append(z);

            //Color (for testing without texture)
            int t = jdmap.getTypeColor(outer*1024+inner);
            Vec4 rgbaOne = jdmap.typeColor(t);
            rgba.append(rgbaOne[0]);//r
            rgba.append(rgbaOne[1]);//g
            rgba.append(rgbaOne[2]);//b
            rgba.append(rgbaOne[3]);//a

            //Texture coords, easy
            GLfloat u = (float)inner / jdmap.getSamples()[0];
            GLfloat v = (float)outer / jdmap.getSamples()[1];
            tex.append(u);
            tex.append(v);
        }
    }

    //And now indexed triangle mesh. These work as well as
    //triangle strips on modern GPUs and are easier
    for(int outer = 0; outer < h-1; outer++)
    {
        for(int inner = 0; inner < w-1; inner++)
        {
            //Two triangles per 4 points, counterclockwise order
            GLuint p1 = (outer * h) + inner;
            GLuint p2 = (outer * h) + inner + 1;
            GLuint p3 = ((outer + 1) * h) + inner;
            GLuint p4 = ((outer + 1) * h) + inner + 1;

            //triangle (p3, p1, p4)
            this->idx.append(p3);
            this->idx.append(p1);
            this->idx.append(p4);
            //triangle (p4, p1, p2)
            this->idx.append(p4);
            this->idx.append(p1);
            this->idx.append(p2);
        }
    }
    //qDebug()<<"tile created:"<<verts.size() <<","<<tex.size()<< ","<< idx.size();
}

void JDTile::render()
{
    //qDebug() << "tile render start";
    glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
        glVertexPointer(3, GL_FLOAT, 0, this->verts.constData());
        jdUtility::CheckGL("glVertexPointer");
        glColorPointer(4, GL_FLOAT, 0, this->rgba.constData());
        jdUtility::CheckGL("glColorPointer");
        glTexCoordPointer(2, GL_FLOAT, 0, this->tex.constData() );
        jdUtility::CheckGL("glTexCoordPointer");
        glDrawElements(GL_TRIANGLES, this->idx.size(), GL_UNSIGNED_INT, this->idx.constData());
        jdUtility::CheckGL("glDrawElements");
    glPopClientAttrib();
    //qDebug()<< "tile render end";
}
