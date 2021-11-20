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
