#include "trafficlight.h"
#include <QWidget>
#include <QLayout>
#include <QRadioButton>
#include<QTimerEvent>
#include<QKeyEvent>
#include<QVector>
#include<QApplication>

TrafficLight::TrafficLight(QWidget * parent): QWidget(parent){

    //Creatign the widgets
    createWidgets();

    //place Widgets
    placeWidgets();
    startTimer(1000);


}

void TrafficLight::createWidgets()
{

  redlight = new QRadioButton;
  redlight->setEnabled(false);
  redlight->toggle();
  redlight->setStyleSheet("QRadioButton::indicator:checked { background-color: red;}");

  yellowlight = new QRadioButton;
  yellowlight->setEnabled(false);
  yellowlight->setStyleSheet("QRadioButton::indicator:checked { background-color: yellow;}");

  greenlight = new QRadioButton;
  greenlight->setEnabled(false);
  greenlight->setStyleSheet("QRadioButton::indicator:checked { background-color: green;}");

currentTime=0;

}


void TrafficLight::placeWidgets()
{

  // Placing the widgets
  auto layout = new QVBoxLayout;

     layout->addWidget(redlight);
  layout->addWidget(yellowlight);
  layout->addWidget(greenlight);

  setLayout(layout);
  currentTime=0;

}
void TrafficLight::timerEvent(QTimerEvent *e){
currentTime++;

    if(redlight->isChecked()&& currentTime==5)
    {yellowlight->toggle();
       currentTime=0;}


    if(yellowlight->isChecked()&& currentTime==2)
    {greenlight->toggle();
        currentTime=0;}






    if(greenlight->isChecked()&& currentTime==2)
    {redlight->toggle();
       currentTime=0;}}

void TrafficLight::keyPressEvent(QKeyEvent *e) {


    if (e->key() == Qt::Key_Escape)
         qApp->exit();
    else  if (e->key() == Qt::Key_R)

        redlight->toggle();
    else  if (e->key() == Qt::Key_Y)

        yellowlight->toggle();
    else  if (e->key() == Qt::Key_G)

        greenlight->toggle();
}
