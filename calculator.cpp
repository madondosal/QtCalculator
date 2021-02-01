#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->calculatorLayout->setFixedSize(450, 240);
    ui->display->setText("0.0");

    QPushButton* numberButtons[10];

    for (int i = 0; i < 10; i++) {
        QString buttonName = "button_" + QString::number(i);
        numberButtons[i] = Calculator::findChild<QPushButton*>(buttonName);

        QObject::connect(numberButtons[i], &QPushButton::released, this, &Calculator::handleNumberButton);
    }

    QObject::connect(ui->button_add_operator, &QPushButton::released, this, &Calculator::handleOperatorButton);
    QObject::connect(ui->button_subtract_operator, &QPushButton::released, this, &Calculator::handleOperatorButton);
    QObject::connect(ui->button_multiply_operator, &QPushButton::released, this, &Calculator::handleOperatorButton);
    QObject::connect(ui->button_divide_operator, &QPushButton::released, this, &Calculator::handleOperatorButton);
    QObject::connect(ui->button_clear, &QPushButton::released, this, &Calculator::handleClearButton);
    QObject::connect(ui->button_equals_operator, &QPushButton::released, this, &Calculator::handleEqualsOperator);
    QObject::connect(ui->button_change_sign, &QPushButton::released, this, &Calculator::handleChangeSignButton);
    QObject::connect(ui->button_memory_add, &QPushButton::released, this, &Calculator::handleMemoryAddButton);
    QObject::connect(ui->button_memory_remove, &QPushButton::released, this, [&](){memory = "no_memory";});
    QObject::connect(ui->button_memory_retrieve, &QPushButton::released, this, &Calculator::handleRetrieveMemoryButton);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::handleNumberButton() {
    QPushButton *senderButton = (QPushButton*)sender();
    QString buttonValue = senderButton->text();
    QString displayValue = ui->display->toPlainText();

    if (displayValue.compare("0.0") == 0|| displayValue.compare("0.0") == 0 || displayValue.compare("Err") == 0) {
        ui->display->setText(buttonValue);
    }else {
        ui->display->setText(displayValue + buttonValue);
    }
}

void Calculator::handleOperatorButton() {

    if (prevOperator == 4 && ui->display->toPlainText().toDouble() == 0) {
        ui->display->setText("Err");
        prevOperator = 0;
        return;
    }

    if (ui->display->toPlainText().isEmpty()){
        ui->display->setText("Err");
        prevOperator = 0;
        return;
    }

    QPushButton *senderButton = (QPushButton*)sender();
    QString senderButtonText = senderButton->text();
    double displayValue = ui->display->toPlainText().toDouble();
    if(prevOperator == 0) {
        prevValue = displayValue;
    }else {
        switch(prevOperator) {
        case 1:
            prevValue += displayValue;
            break;
        case 2:
            prevValue -= displayValue;
            break;
        case 3:
            prevValue *= displayValue;
            break;
        case 4:
            prevValue /= displayValue;
            break;
        }

    }
    if (senderButtonText.compare("+") == 0){prevOperator = 1;}
    if (senderButtonText.compare("-") == 0){prevOperator = 2;}
    if (senderButtonText.compare("*") == 0){prevOperator = 3;}
    if (senderButtonText.compare("/") == 0){prevOperator = 4;}
    ui->display->clear();
}

void Calculator::handleEqualsOperator() {

    if (prevOperator == 4 && ui->display->toPlainText().toDouble() == 0) {
        ui->display->setText("Err");
        prevOperator = 0;
        return;
    }

    if (ui->display->toPlainText().isEmpty()){
        return;
    }


    double displayValue = ui->display->toPlainText().toDouble();

    if (prevOperator == 0) {
        prevValue = displayValue;
    }

    switch(prevOperator) {
    case 1:
        prevValue += displayValue;
        break;
    case 2:
        prevValue -= displayValue;
        break;
    case 3:
        prevValue *= displayValue;
        break;
    case 4:
        prevValue /= displayValue;
        break;
    }

    ui->display->setText(QString::number(prevValue));
    prevOperator = 0;
}

void Calculator::handleClearButton() {
    prevOperator = 0;
    ui->display->setText("0.0");
}

void Calculator::handleChangeSignButton() {
    QString displayValue = ui->display->toPlainText();
    if (displayValue.compare("Err") == 0) {return;}
    if (displayValue.isEmpty() || displayValue.toDouble() == 0) {return;}
    double dblDisplayValue = displayValue.toDouble();
    dblDisplayValue *= -1;
    ui->display->setText(QString::number(dblDisplayValue));

}

void Calculator::handleMemoryAddButton() {
    QString displayValue = ui->display->toPlainText();

    if (displayValue.isEmpty() || displayValue.compare("Err") == 0) {return;}

    memory = displayValue;
}

void Calculator::handleRetrieveMemoryButton() {
    if(memory.compare("no_memory") == 0) {
        return;
    }
    QString displayValue = ui->display->toPlainText();
    if(displayValue.isEmpty() || displayValue.compare("Err") == 0){
        ui->display->setText(memory);
    }
}







