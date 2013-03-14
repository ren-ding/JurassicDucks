/**
 *
 *  @file jdflockdialog.cpp
 *
 *  @brief The class is a flocking factors setting dialog.
 *
 *  @author Ren DING
 *  @date 24/09/12.
 *
 */

#include "jdflockdialog.h"
#include "jdfactors.h"

JDFlockDialog::JDFlockDialog(QWidget *parent, QString fname)
    :QDialog(parent)
{
    this->filename = fname;

    QMap<QString, float> factorMap = readMap(filename);
    //construct and initialized label and line edit
    seperationLabel = new QLabel(tr("SeperationFactor"));
    seperationLineEdit = new QLineEdit(QString::number(factorMap.value("seperationFactor")));
    seperationLabel->setBuddy(seperationLineEdit);

    viewRadiusLabel = new QLabel(tr("ViewRadiusFactor"));
    viewRadiusLineEdit = new QLineEdit(QString::number(factorMap.value("viewRadiusFactor")));
    viewRadiusLabel->setBuddy(viewRadiusLineEdit);

    steeringForceLabel = new QLabel(tr("SteeringForceFactor"));
    steeringForceLineEdit = new QLineEdit(QString::number(factorMap.value("steeringForceFactor")));
    steeringForceLabel->setBuddy(steeringForceLineEdit);

    visibilityLabel = new QLabel(tr("VisibilityFactor"));
    visibilityLineEdit = new QLineEdit(QString::number(factorMap.value("visibilityFactor")));
    visibilityLabel->setBuddy(visibilityLineEdit);

    //construct and initialized  button
    settingButton = new QPushButton(tr("Set"));
    //settingButton with this property set to true, will automatically be pressed when the user presses enter
    settingButton->setDefault(true);
    closeButton = new QPushButton(tr("Close"));

    connect(settingButton, SIGNAL(clicked()), this, SLOT(setClicked()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    //set layout
    QHBoxLayout* labelLineEdit1 = new QHBoxLayout();
    labelLineEdit1->addWidget(seperationLabel);
    labelLineEdit1->addWidget(seperationLineEdit);

    QHBoxLayout* labelLineEdit2 = new QHBoxLayout();
    labelLineEdit2->addWidget(viewRadiusLabel);
    labelLineEdit2->addWidget(viewRadiusLineEdit);

    QHBoxLayout* labelLineEdit3 = new QHBoxLayout();
    labelLineEdit3->addWidget(steeringForceLabel);
    labelLineEdit3->addWidget(steeringForceLineEdit);

    QHBoxLayout* labelLineEdit4 = new QHBoxLayout();
    labelLineEdit4->addWidget(visibilityLabel);
    labelLineEdit4->addWidget(visibilityLineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(settingButton);
    buttonLayout->addWidget(closeButton);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(labelLineEdit1);
    mainLayout->addLayout(labelLineEdit2);
    mainLayout->addLayout(labelLineEdit3);
    mainLayout->addLayout(labelLineEdit4);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Factor Setting"));
    setFixedHeight(sizeHint().height());
}

JDFlockDialog::~JDFlockDialog()
{
}

void JDFlockDialog::setClicked()
{
    QString seperationText = seperationLineEdit->text();
    QString viewRadiusText = viewRadiusLineEdit->text();
    QString steeringForceText = steeringForceLineEdit->text();
    QString visibilityText = visibilityLineEdit->text();

    QMap<QString, float> map;
    map.insert("seperationFactor",seperationText.toFloat());
    map.insert("viewRadiusFactor",viewRadiusText.toFloat());
    map.insert("steeringForceFactor",steeringForceText.toFloat());
    map.insert("visibilityFactor",visibilityText.toFloat());

    writeMap(map,filename);
}

