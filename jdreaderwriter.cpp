/**
 *
 *  @file jdreaderwriter.cpp
 *
 *  @brief The class is for reading and writing text file.
 *
 *  @author Ren DING
 *  @date 23/09/12.
 *
 */

#include "jdreaderwriter.h"

//
// read from file and convert it to QMap data structure
//
QMap<QString, float> readMap(QString filename)
{
    QMap<QString, float> map;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        qWarning() <<"Cannot read file";

    QTextStream stream ( &file );
    QString line;
    while( !stream.atEnd() )
    {
         line = stream.readLine();
         QStringList lineSplit = line.split(",");
         map.insert(lineSplit[0],lineSplit[1].toFloat());
    }
    file.close();

    return map;
}

//
// write QMap structure data to file
//
void writeMap(QMap<QString, float> map, QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
        qWarning() <<"Cannot write file";

    QTextStream stream(&file);

    QMap<QString, float>::iterator iter;
    for (iter = map.begin(); iter != map.end(); iter++)
        stream << iter.key() << "," << iter.value() << endl;

    file.close();
}
