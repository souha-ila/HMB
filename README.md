![logo](https://ueuromed.org/sites/default/files/2020-02/eidia.png)
# **RAPPORT DE TP: [Signal and Slots](https://anassbelcaid.github.io/CS311/forms/)**
## OBJECTIF DE TP:
<ul>
  <li>Implémente votre premier widget interactif Gui.</li>
</ul>


## INTRODUCTION: 
<p> Dans la programmation GUI, lorsque nous modifions un widget, nous voulons souvent qu'un autre widget soit notifié. Plus généralement, on veut que les objets de toute nature puissent communiquer entre eux. Par exemple, si un utilisateur clique sur un bouton Fermer , nous souhaitons probablement que la fonction close() de la fenêtre soit appelée.

</p>

<p> D'autres boîtes à outils réalisent ce type de communication en utilisant des rappels. Un rappel est un pointeur vers une fonction, donc si vous voulez qu'une fonction de traitement vous informe d'un événement, vous passez un pointeur vers une autre fonction (le rappel) à la fonction de traitement. La fonction de traitement appelle ensuite le rappel lorsque cela est approprié. Bien qu'il existe des frameworks efficaces utilisant cette méthode, les rappels peuvent ne pas être intuitifs et peuvent présenter des problèmes pour garantir l'exactitude du type des arguments de rappel.</p>


##  Traffic Light 

 le but de cet exercice est  d'utiliser le [QTimer](https://doc.qt.io/qt-5/qtimer.html) pour simuler ~~**un feu de circulation**~~  



<p>On va traiter 2 cas :</p>
<ul>
Le premeir cas c'est juste l'activation des boutons  dans l'ordre suivant: Red -> Green -> Yellow
</ul>
Pour realiser ce but le code est le suivant:
 dans *TrafficLight.H*:
 

```cpp
#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <QWidget>
#include <QTimerEvent>

class QRadioButton;

class TrafficLight: public QWidget{
  Q_OBJECT

public:

  TrafficLight(QWidget * parent = nullptr);

protected:
     void createWidgets();
     void placeWidgets();

private:
     //surcharge la fonction d'ecoputr de temps
     void timerEvent(QTimerEvent *e);


  QRadioButton * redlight;
  QRadioButton * yellowlight;
  QRadioButton * greenlight;

};


#endif 
```

dans *trafficligh.cpp* :

```cpp
#include "trafficlight.h"
#include <QWidget>
#include <QLayout>
#include <QRadioButton>
#include <QTimerEvent>

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
  redlight->toggle();//pour activer le boutton
  redlight->setStyleSheet("QRadioButton::indicator:checked { background-color: red;}");

  yellowlight = new QRadioButton;
  yellowlight->setEnabled(false);
  yellowlight->setStyleSheet("QRadioButton::indicator:checked { background-color: yellow;}");


  greenlight = new QRadioButton;
  greenlight->setEnabled(false);
  greenlight->setStyleSheet("QRadioButton::indicator:checked { background-color: green;}");
}


void TrafficLight::placeWidgets()
{

  // Placing the widgets
  auto layout = new QVBoxLayout;
  layout->addWidget(redlight);
  layout->addWidget(yellowlight);
  layout->addWidget(greenlight);
  setLayout(layout);

}
void TrafficLight::timerEvent(QTimerEvent *e)
{

// si le rouge est activer ==> activer yellow

    if(redlight->isChecked())
        yellowlight->toggle();
// si le yellow est activer ==> activer le green
   else if(yellowlight->isChecked())
        greenlight->toggle();

// si le green est activer ==> activer le rouge
    else if(greenlight->isChecked())
        redlight->toggle();
}
```

dans *Main*:
```cpp
#include <QApplication>
#include "trafficlight.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //Creating the traffic light
    auto light = new TrafficLight;


    //showing the trafic light
    light->show();

    return a.exec();
}
```
 
 On peut aussi faire  le travail avec des Vecteurs:
 
 dans le *trafficligh.h* :
 ```cpp
 #include <QWidget>
#include <QTimerEvent>
#include <QVector>

class QRadioButton;

class TrafficLight: public QWidget{
  Q_OBJECT

public:

  TrafficLight(QWidget * parent = nullptr);

protected:
     void createWidgets();
     void placeWidgets();

private:
     //surcharge la fonction d'ecoputr de temps
     void timerEvent(QTimerEvent *e);


  QRadioButton * redlight;
  QRadioButton * yellowlight;
  QRadioButton * greenlight;
  QVector<QRadioButton*>lights;

  int index;
  int time[3]{4,1,2};
  int currentTime;

};

 ```
 dans *trafficligh.cpp* :
 ```cpp
 #include "trafficlight.h"
#include <QWidget>
#include <QLayout>
#include <QRadioButton>
#include <QTimerEvent>
#include <QVector>
#include<QTime>
TrafficLight::TrafficLight(QWidget * parent): QWidget(parent){

    //Creatign the widgets
    createWidgets();

    //place Widgets
    placeWidgets();

lights.append(redlight);
lights.append(yellowlight);
lights.append(greenlight);
index=0;
    startTimer(1000);
}

void TrafficLight::createWidgets()
{

  redlight = new QRadioButton;
  redlight->setEnabled(false);
  redlight->toggle();//pour activer le boutton
  redlight->setStyleSheet("QRadioButton::indicator:checked { background-color: red;}");

  yellowlight = new QRadioButton;
  yellowlight->setEnabled(false);
  yellowlight->setStyleSheet("QRadioButton::indicator:checked { background-color: yellow;}");

  greenlight = new QRadioButton;
  greenlight->setEnabled(false);
  greenlight->setStyleSheet("QRadioButton::indicator:checked { background-color: green;}");
}


void TrafficLight::placeWidgets()
{

  // Placing the widgets
  auto layout = new QVBoxLayout;
  layout->addWidget(redlight);
  layout->addWidget(yellowlight);
  layout->addWidget(greenlight);
  setLayout(layout);

}
void TrafficLight::timerEvent(QTimerEvent *e)
{

index = (index +1) % 3;
lights[index]->toggle();
}

 ```
 
------>*le Resultat* est :


 ![resulat1](https://raw.githubusercontent.com/souha-ila/HMB/master/1.gif)



<ul>
Le 2eme cas cest lactivation des boutons avec un certain timing:
</ul>

dans  *TrafficLight.h*:

```cpp
#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H
#include<QVector>
#include <QWidget>

class QRadioButton;

class TrafficLight: public QWidget{
  Q_OBJECT

public:

  TrafficLight(QWidget * parent = nullptr);

protected:
     void createWidgets();
     void placeWidgets();
     void timerEvent(QTimerEvent *e) override ;
  void keyPressEvent(QKeyEvent *e) override;




private:

  QRadioButton * redlight;
  QRadioButton * yellowlight;
  QRadioButton * greenlight;

int currentTime;

};


#endif


```
dans *TrafficLight.cpp*:
```cpp
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


```

  ------>*le Resultat* est :


   ![resulat2](https://github.com/souha-ila/HMB/blob/master/cas%20final.gif)

 
## Calculator
 Cet exercice poursuit pour ajouter des fonctionnalités interactives aux widgets de la calculatrice écrits dans [le devoir](https://github.com/souha-ila/Rapport2) précédent.
 L'objectif est d'utiliser des signaux et des slots pour simuler le comportement d'une calculatrice de base. Les opérations prises en charge sont *, +, -, /.


Le code pour atteindre ce but est :
dans *Calulator.h*:
```cpp
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLCDNumber>
#include<QLineEdit>
#include<QToolButton>


class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
private:
    int * left;          //left operand
    int * right;         // right operand
    QString *operation;  // Pointer on the current operation




 // Add you custom slots here

protected:
    void createWidgets();        //Function to create the widgets
    void placeWidget();         // Function to place the widgets


//events
protected:
    void keyPressEvent(QKeyEvent *e)override;     //Override the keypress events
public slots:
   void newDigit();
    void changeOperation();
    void buttonenter();



private:
    QGridLayout *buttonsLayout; // layout for the buttons
    QVBoxLayout *layout;        //main layout for the button
    QVector<QPushButton*> digits;  //Vector for the digits
    QPushButton *enter;

            // Where to display the numbers


    int *a;
    QVector<QPushButton*> operations; //operation buttons
    QLCDNumber *disp;
    //     QString* lesoperateurs;
    //      int o;
              // enter button
         //operation buttons
                 // Where to display the numbers
        QVector<QString*> vector;

};

#endif // CALCULATOR_H

```

dans *Calulator.cpp*:
```cpp
#include "calculator.h"
#include <QKeyEvent>
#include <QApplication>
#include<QLCDNumber>


Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    createWidgets();
    placeWidget();

    left=nullptr;
    right=nullptr;
    operation=nullptr;
    a=nullptr;





}




Calculator::~Calculator()
{
    delete disp;
    delete layout;
    delete buttonsLayout;
}


void Calculator::createWidgets()
{
    //Creating the layouts
    layout = new QVBoxLayout();
    layout->setSpacing(2);

    //grid layout
    buttonsLayout = new QGridLayout;


    //creating the buttons
    for(int i=0; i < 10; i++)
    {
        digits.push_back(new QPushButton(QString::number(i)));
        digits.back()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        digits.back()->resize(sizeHint().width(), sizeHint().height());
               digits.back()->setStyleSheet("background-color:rgba(229, 152, 102);");

    }
    //enter button
    enter = new QPushButton("Enter",this);
    enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    enter->resize(sizeHint().width(), sizeHint().height());
   enter->setStyleSheet("background-color: rgb(120, 66, 18);");

    //operatiosn buttons
    operations.push_back(new QPushButton("+"));
    operations.back()->setStyleSheet("background-color:rgb(186, 74, 0);");
    operations.push_back(new QPushButton("-"));
     operations.back()->setStyleSheet("background-color:rgb(186, 74, 0);");
    operations.push_back(new QPushButton("*"));
     operations.back()->setStyleSheet("background-color:rgb(186, 74, 0);");
    operations.push_back(new QPushButton("/"));
     operations.back()->setStyleSheet("background-color:rgb(186, 74, 0);");


    //creating the lcd
    disp = new QLCDNumber(this);
    disp->setDigitCount(6);
    buttonsLayout = new QGridLayout;
disp->setStyleSheet("background-color:rgb(246, 221, 204);");

}

void Calculator::placeWidget()
{

    layout->addWidget(disp);
    layout->addLayout(buttonsLayout);


    //adding the buttons
    for(int i=1; i <10; i++)
        buttonsLayout->addWidget(digits[i], (i-1)/3, (i-1)%3);


    //Adding the operations
    for(int i=0; i < 4; i++)
        buttonsLayout->addWidget(operations[ i], i, 4);



    //Adding the 0 button
    buttonsLayout->addWidget(digits[0], 3, 0);
    buttonsLayout->addWidget(enter, 3, 1, 1,2);

      setLayout(layout);
  //Connecting the digits
  for(int i=0; i <10; i++)
      connect(digits[i], &QPushButton::clicked,
              this, &Calculator::newDigit);


  for(int j=0; j <4; j++)
      connect(operations[j], &QPushButton::clicked,
              this, &Calculator::changeOperation);
   connect(enter,&QPushButton::clicked,this,&Calculator::buttonenter);
}


void Calculator::newDigit(){


        //getting the sender
        auto button = dynamic_cast<QPushButton*>(sender());

        //getting the value
        int value = button->text().toInt();

        //Check if we have an operation defined
        if(operation)
        {
            //check if we have a value or not
            if(!right)
                right = new int{value};
            else
                *right = 10 * (*right) + value;

            disp->display(*right);

        }
        else
        {
            if(!left)
                left = new int{value};
            else
                *left = 10 * (*left) + value;

            disp->display(*left);


}
}
void Calculator::keyPressEvent(QKeyEvent *e)
{
    //Exiting the application by a click on space
    if( e->key() == Qt::Key_Escape)
        qApp->exit(0);


         }



void Calculator::changeOperation()
{

    if(vector.isEmpty()){
        //Getting the sender button
        auto button = dynamic_cast<QPushButton*>(sender());

        //Storing the operation
        operation = new QString{button->text()};


     vector << this->operation;

     disp->display(*operation);



    }
    else{
        //Getting the sender button
        auto button = dynamic_cast<QPushButton*>(sender());

        //Storing the operation
        operation = new QString{button->text()};
     vector << this->operation;

     if(vector.at(*a)==QString("+"))
     *left=(*left)+(*right);

     if(vector.at(*a)==QString("*"))
     *left=(*left)*(*right);
     if(vector.at(*a)==QString("-"))
     *left=(*left)-(*right);
     if(vector.at(*a)==QString("/"))
     *left=(*left)/(*right);


    }

}

void Calculator::buttonenter(){
    if(this->operation==QString("+"))
    disp->display((*left)+(*right));

    if(this->operation==QString("*"))
    disp->display((*left)*(*right));

    if(this->operation==QString("-"))
    disp->display((*left)-(*right));

    if(this->operation==QString("/"))
    disp->display((*left)/(*right));


}


```
dans *main*:
```cpp
#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    w.setWindowTitle("Calculator");
    w.resize(500,500);
    w.show();
    return a.exec();
}
```


=> ~~**LE RESULTAT**~~ :


![imagecalc](https://raw.githubusercontent.com/souha-ila/HMB/master/Calculator%202021-11-20%2016-39-08%20(1).gif)



 ## CONCLUSION:
 
Qt est une communication très efficace entre les composants, les signaux et les slots, il est également très simple pour les développeurs.
              
       


  ## > Realisé par:  *OUNAR Souhaila*
![image](https://raw.githubusercontent.com/souha-ila/HMB/master/anim.gif)
 

 
 
 
