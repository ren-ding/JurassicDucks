/**
 *
 *  @file jdflockdialog.h
 *
 *  @brief The head file of jdflockdialog.cpp
 *
 *  @author Ren DING
 *  @date 24/09/12.
 *
 */

#ifndef __JDFLOCKDIALOGH__
#define __JDFLOCKDIALOGH__

#include "headers.h"
#include "jdreaderwriter.h"

class JDFlockDialog : public QDialog
{
    Q_OBJECT

public:
    JDFlockDialog(QWidget *parent, QString filename);
    ~JDFlockDialog();
protected slots:
    void setClicked();
private:
    QString filename;
    QLabel *seperationLabel;
    QLineEdit *seperationLineEdit;
    QLabel *viewRadiusLabel;
    QLineEdit *viewRadiusLineEdit;
    QLabel *steeringForceLabel;
    QLineEdit *steeringForceLineEdit;
    QLabel *visibilityLabel;
    QLineEdit *visibilityLineEdit;
    QPushButton *settingButton;
    QPushButton *closeButton;
};

#endif // __JDFLOCKDIALOGH__
