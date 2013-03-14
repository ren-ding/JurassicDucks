/**
 *
 *  @file main.cpp
 *
 *  @brief The main class
 *
 *  @author Ren DING
 *  @date 02/08/12.
 *
 */

#include "headers.h"
#include "jdUtility.h"
#include "jduckswindow.h"
#include "jduckswidget.h"

//Global variable

JDucksWindow * pMainWindow;


//
// Frame work functions
//

static bool Setup()
{
    //
    //initialized the main window frame
    //
    pMainWindow = new JDucksWindow(NULL);

    if (!jdUtility::InitGLWindow(pMainWindow, 800, 600, false))
        qWarning() <<"please check window initialization";

    //show main window
    pMainWindow->show();

    return true;
}

int main(int argc, char *argv[])
{
    QApplication *  pApp = new QApplication(argc, argv);

    if (!Setup())
        qWarning() <<"Cannot setup, please check Setup";

    return pApp->exec();
}
