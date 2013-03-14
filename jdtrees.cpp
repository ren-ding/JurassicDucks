/**
 *
 *  @file jdtrees.cpp
 *
 *  @brief Tree batch. All the trees sharing one texture.
 *  Switching textures is reasonably expensive, so it is much faster
 *  to render all the geometry that uses a texture map in one go.
 *
 *  @author Ren DING
 *  @date 09/10/12.
 *
 */

#include "headers.h"
#include "jdtrees.h"
#include "jdtree.h"
#include "jdmap.h"
#include "jdUtility.h"
#include "jdfactors.h"

static const float _TY  = 10.0;      // Default height in metres
static const float _hW  = 2.5;       // Default half width

static GLfloat treeVerts[12][3] = {
    {-_hW, _TY, 0},
    {-_hW, 0, 0},
    {_hW, _TY, 0},

    {-_hW, 0, 0},
    {_hW, 0, 0},
    {_hW, _TY, 0},

    {0, _TY, -_hW},
    {0, 0, -_hW},
    {0, _TY, _hW},

    {0, 0, -_hW},
    {0, 0, _hW},
    {0, _TY, _hW}
};

static GLfloat treeTex[12][2] = {
    {0, 1},
    {0, 0},
    {1, 1},

    {0, 0},
    {1, 0},
    {1, 1},

    {0, 1},
    {0, 0},
    {1, 1},

    {0, 0},
    {1, 0},
    {1, 1},
};

static GLfloat treeRGBA[12][4] = {
    {0, 1, 0, 1},
    {0, 1, 0, 1},
    {0, 1, 0, 1},

    {0, 1, 0, 1},
    {0, 1, 0, 1},
    {0, 1, 0, 1},

    {0, 1, 0, 1},
    {0, 1, 0, 1},
    {0, 1, 0, 1},

    {0, 1, 0, 1},
    {0, 1, 0, 1},
    {0, 1, 0, 1}
};

JDTrees::JDTrees()
{
    isRoot = true;
}

JDTrees::JDTrees(JDMap jdmap)
{
    isRoot = true;

    //use for counting how many different types are present
    //the number of tree texture should less than tagSize
    tagSize = 10;

    tagList = new bool[tagSize];
    for(int i = 0;i < tagSize;i++)
    {
        tagList[i] = false;
    }

    //Start by reading in all trees
    QFile file(appPath+jdmap.getDirName() + "/trees.txt");
    if (!file.open(QIODevice::ReadOnly))
        qWarning() <<"Cannot read trees.txt";

    QTextStream stream ( &file );
    QString line;
    while( !stream.atEnd() )
    {
        line = stream.readLine();
        //Skip blank lines and comments
        if(line.length() == 0 || line.startsWith("#"))
            continue;
        //Comma separated values
        QStringList lineSplit = line.split(",");
        //Must have position
        float x = lineSplit.at(0).toFloat()* jdmap.getScale();
        float z = lineSplit.at(1).toFloat()* jdmap.getScale();
        int t = 0;
        if(lineSplit.size() == 3)
            t = lineSplit.at(2).toFloat();

        //Keep record of how many different types are present
        tagList[t] = true;
        //Scale factors also optional
        float hs = 1.0;
        float vs = 1.0;
        if(lineSplit.size() == 5)
        {
            hs = lineSplit.at(3).toFloat();
            vs = lineSplit.at(4).toFloat();
        }

        //create tree
        trees.append(JDTree(x, 0.0, z, t, hs, vs));
    }
    file.close();
}

JDTrees::JDTrees(QVector<JDTree> trees,QString fileName)
{
    isRoot = false;
    this->trees = trees;

    QImage img;
    img.load(appPath+fileName);
    //OpenGL expects image data to start at bottom left
    img = img.mirrored(false);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

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

    //qDebug()<<"Loaded tree image";
}


QVector<JDTree> JDTrees::getTrees() const
{
    return this->trees;
}

void JDTrees::render(bool shaded)
{
    //two levels tree structure
    //check if it is the root trees

    if(isRoot)
    {
        QVector<JDTrees>::iterator batchesIter;
        for(batchesIter = batches.begin(); batchesIter < batches.end(); batchesIter++)
        {
            JDTrees batch = *batchesIter;
            batch.render(shaded);
        }
    }
    else
    {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        if(shaded && this->texID > 0)
        {
            glDisable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
            glBindTexture(GL_TEXTURE_2D, texID);
            jdUtility::CheckGL("glBindTexture");
        }
        else if (shaded)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        QVector<JDTree>::iterator treeIter;
        for(treeIter = this->trees.begin(); treeIter < this->trees.end(); treeIter++)
        {
            JDTree tree = *treeIter;

            //render each tree, each tree has own position
            glPushMatrix();
                glTranslatef(tree.getPosX(), tree.getPosY(), tree.getPosZ());
                //Each tree can also be scaled from default size
                glScalef(tree.getHScale(), tree.getVScale(), tree.getHScale());
                //And draw
                glVertexPointer(3, GL_FLOAT, 0, treeVerts);
                jdUtility::CheckGL("glVertexPointer");
                glColorPointer(4, GL_FLOAT, 0,  treeRGBA);
                jdUtility::CheckGL("glColorPointer");
                glTexCoordPointer(2, GL_FLOAT, 0, treeTex);
                jdUtility::CheckGL("glTexCoordPointer");
                glDrawArrays(GL_TRIANGLES, 0, 12);
                jdUtility::CheckGL("glDrawArrays");
            glPopMatrix();
        }
        glPopClientAttrib();
        glPopAttrib();
    }
}

void JDTrees::loadFromFile(QString dirName)
{
    // Now group trees by type
    for(int i = 0; i<tagSize; i++)
    {
        //Grab one type
        if(tagList[i])
        {
            QVector<JDTree> subTrees;
            QVector<JDTree>::iterator treeIter;
            for(treeIter = trees.begin(); treeIter < trees.end(); treeIter++)
            {
                JDTree tree = *treeIter;
                if(tree.getTag() == i)
                    subTrees.append(tree);
            }
            QString texName = dirName + "/tree" + QString::number(i) + ".png";

            this->batches.append(JDTrees(subTrees,texName));
        }
    }

    delete tagList;
    tagList = 0;
}
