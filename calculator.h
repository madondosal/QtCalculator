#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();
public slots:
    void handleNumberButton();
    void handleOperatorButton();
    void handleEqualsOperator();
    void handleClearButton();
    void handleChangeSignButton();
    void handleMemoryAddButton();
    void handleRetrieveMemoryButton();

private:
    Ui::Calculator *ui;
    int prevOperator = 0;

    /* Addintion = 1
     * Subtraction = 2
     * Multiplication = 3
     * Division =4
     * */

    double prevValue;
    QString memory = "no_memory";
};

#endif // CALCULATOR_H
