/**
 *
 *  @file jdtrees.h
 *
 *  @brief The head file of jdtiles.cpp
 *
 *  @author Ren DING
 *  @date 09/10/12.
 *
 */

#ifndef __JDTREESH__
#define __JDTREESH__

#include "headers.h"
#include "jdtree.h"
class JDMap;

class JDTrees
{
protected:
    bool isRoot;
    int tagSize;
    bool* tagList;

    GLuint texID;
    QVector<JDTree> trees;
    QVector<JDTrees> batches;
public:
    JDTrees();
    JDTrees(JDMap jdmap);
    JDTrees(QVector<JDTree> trees,QString fileName);

    QVector<JDTree> getTrees() const;

    void render(bool shaded);
    void loadFromFile(QString dirName);
};

#endif // __JDTREESH__
