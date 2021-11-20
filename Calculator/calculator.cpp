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

